#include "Fractal_Element.h"

Fractal_Element::Fractal_Element(std::vector<Line>* _statics):
     m_baseline(Line::lt_base, sf::Vector2f(0,0), sf::Vector2f(0,0)),
     statics(_statics),
     m_statics_end(_statics->end()),
     m_maxLength(0)
{

}

Fractal_Element::~Fractal_Element() {

}

double Fractal_Element::BaseLength() {
    return m_baseline.Length();
}

double Fractal_Element::GetMaxLength() {
    return m_maxLength;
}

void Fractal_Element::AddLine(Line newLine) {
    switch (newLine.GetType()) {
    case Line::line_type::lt_hidden:
        // Hidden lines are useless for iteration, so don't keep track of them.
        break;
    case Line::line_type::lt_static:
        statics->push_back(newLine);
        m_statics_end = statics->end();
        break;
    default:
        m_lines.push_back(newLine);
        double newLen = newLine.Length();
        if(newLen > m_maxLength)
            m_maxLength = newLen;
        break;
    }
}

const std::vector<Line>& Fractal_Element::GetLines() const {
    return m_lines;
}

Fractal_Element Fractal_Element::ReplaceAll(const Fractal_Template& target) const {
    Fractal_Element newFE(statics);
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        Fractal_Template transformed = target.TransformAll(target.MatchBase(*line_it));
        std::vector<Line> transLines = transformed.GetLines();
        for(auto trans_it = transLines.begin(); trans_it != transLines.end(); trans_it++) {
            Line transformed_line = *trans_it;
            if(transformed_line.Length() < INFINITY_STOP_SIZE)
                transformed_line.SetType(Line::lt_static);
            newFE.AddLine(transformed_line);
        }
    }
    newFE.SetBase(m_baseline.GetStart(), m_baseline.GetFinish());
    return newFE;
}

void Fractal_Element::Draw(sf::RenderWindow& window, bool simple) const {
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        line_it->Draw(window, simple);
    }
    for(auto line_it = statics->begin(); line_it != m_statics_end; line_it++) {
        line_it->Draw(window, simple);
    }
    m_baseline.Draw(window, simple);
}

void Fractal_Element::SetBase(sf::Vector2f start, sf::Vector2f finish) {
    m_baseline.SetPosition(start, finish);
}

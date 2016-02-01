#include "Fractal_Element.h"

Fractal_Element::Fractal_Element():
     m_baseline(Line::lt_base, sf::Vector2f(0,0), sf::Vector2f(0,0))
{

}

Fractal_Element::~Fractal_Element() {

}

void Fractal_Element::AddLine(Line newLine) {
    m_lines.push_back(newLine);
    m_baseline.SetPosition(m_lines[0].GetStart(), newLine.GetFinish());
}

const std::vector<Line>& Fractal_Element::GetLines() const {
    return m_lines;
}

Transform Fractal_Element::MatchBase(const Line& base) const {
    return m_baseline.Match(base);
}

Fractal_Element Fractal_Element::TransformAll(Transform t) const {
    Fractal_Element newFE;
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        newFE.AddLine(line_it->ApplyTransform(t));
    }
    return newFE;
}

Fractal_Element Fractal_Element::ReplaceAll(const Fractal_Element& target) const {
    Fractal_Element newFE;
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        if(line_it->GetType() == Line::lt_static || line_it->GetType() == Line::lt_hidden) {
            newFE.AddLine(*line_it);
            continue;
        }
        Fractal_Element transformed = target.TransformAll(target.MatchBase(*line_it));
        std::vector<Line> transLines = transformed.GetLines();
        for(auto trans_it = transLines.begin(); trans_it != transLines.end(); trans_it++) {
            newFE.AddLine(*trans_it);
        }
    }
    newFE.SetBase(m_baseline.GetStart(), m_baseline.GetFinish());
    return newFE;
}

void Fractal_Element::Draw(sf::RenderWindow& window, bool simple) const {
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        line_it->Draw(window, simple);
    }
    m_baseline.Draw(window, simple);
}

void Fractal_Element::SetBase(sf::Vector2f start, sf::Vector2f finish) {
    m_baseline.SetPosition(start, finish);
}

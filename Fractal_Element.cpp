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

Transform Fractal_Element::MatchBase(const Line& base) {
    return m_baseline.Match(base);
}

Fractal_Element Fractal_Element::TransformAll(Transform t) {
    Fractal_Element newFE;
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        if(line_it->GetType() == Line::lt_static || line_it->GetType() == Line::lt_hidden)
            newFE.AddLine(*line_it);
        else
            newFE.AddLine(line_it->ApplyTransform(t));
    }

    return newFE;
}

void Fractal_Element::Draw(sf::RenderWindow& window, bool simple) {
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        line_it->Draw(window, simple);
    }
    m_baseline.Draw(window, simple);
}

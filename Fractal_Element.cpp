#include "Fractal_Element.h"

Fractal_Element::Fractal_Element(sf::RenderWindow* window):
     m_window(window),
     m_baseline(window, Line::lt_base, sf::Vector2f(0,0), sf::Vector2f(0,0))
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
    Fractal_Element newFE(m_window);
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        if(line_it->GetType() == Line::lt_static || line_it->GetType() == Line::lt_hidden)
            newFE.AddLine(*line_it);
        else
            newFE.AddLine(line_it->ApplyTransform(t));
    }

    return newFE;
}

void Fractal_Element::Draw(bool simple) {
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        line_it->Draw(simple);
    }
    m_baseline.Draw(simple);
}

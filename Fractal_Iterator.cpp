#include "Fractal_Iterator.h"
#include "config.h"
#include "constants.h"

Fractal_Iterator::Fractal_Iterator()
{
    m_levels.push_back(Fractal_Element(&m_statics));
    m_currentLevel = 0;
};

Fractal_Iterator::~Fractal_Iterator() {

}

void Fractal_Iterator::Draw(sf::RenderTarget& target) {
    m_levels[m_currentLevel].Draw(target, true);
}

void Fractal_Iterator::SetBase(Fractal_Template newBase) {
    m_levels.clear();
    m_statics.clear();
    m_base = newBase;

    Fractal_Element element(&m_statics);

    Line newBaseline = m_base.GetBase();
    newBaseline.SetColor(sf::Color::Black);
    newBaseline.SetType(Line::line_type::lt_topRight);

    element.AddLine(newBaseline);
    element.SetBase(newBaseline.GetStart(), newBaseline.GetFinish());

    m_levels.push_back(element);
    SetLevel(0);
}

void Fractal_Iterator::SetLevel(size_t level) {
    if(level > ITERATOR_LEVELS) {
        m_currentLevel = ITERATOR_LEVELS + 1;
        IterateToInfinity();
    } else {
        m_currentLevel = level;
        IterateTo(level);
    }
}

void Fractal_Iterator::IterateTo(size_t level) {
    if(level < m_levels.size())
        return;
    for(size_t iii = m_levels.size(); iii <= level; iii++) {
        Fractal_Element nextFE = m_levels[iii - 1].ReplaceAll(m_base);
        m_levels.push_back(nextFE);
    }
}

void Fractal_Iterator::IterateToInfinity() {
    // If we already iterated to infinity once before
    if (m_levels.size() > ITERATOR_LEVELS + 1)
        return;

    IterateTo(ITERATOR_LEVELS);
    Fractal_Element nextFe = m_levels[ITERATOR_LEVELS];
    while (nextFe.GetMaxLength() > INFINITY_STOP_SIZE) {
        nextFe = nextFe.ReplaceAll(m_base);
    }
    m_levels.push_back(nextFe);
}

#include "Fractal_Iterator.h"

Fractal_Iterator::Fractal_Iterator() :
    m_levels(0)
{
    m_levels.push_back(Fractal_Element());
    m_currentLevel = 0;
};

Fractal_Iterator::~Fractal_Iterator() {

}

void Fractal_Iterator::Draw(sf::RenderWindow& window) {
    m_levels[m_currentLevel].Draw(window, true);
}

void Fractal_Iterator::SetBase(Fractal_Element newBase) {
    m_levels.clear();
    m_levels.push_back(newBase);
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
        Fractal_Element nextFE = m_levels[iii - 1].ReplaceAll(m_levels[0]);
        m_levels.push_back(nextFE);
    }
}

void Fractal_Iterator::IterateToInfinity() {
    IterateTo(ITERATOR_LEVELS);
    Fractal_Element nextFe = m_levels[m_levels.size() - 1];
    while (nextFe.BaseLength() > 10)
        nextFe = nextFe.ReplaceAll(m_levels[0]);

    if (m_levels.size() <= ITERATOR_LEVELS)
        m_levels.pop_back();

    m_levels.push_back(nextFe);
}

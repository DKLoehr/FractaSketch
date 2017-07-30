#ifndef FRACTAL_ITERATOR_H
#define FRACTAL_ITERATOR_H

#include "Fractal_Template.h"
#include "Fractal_Element.h"

class Fractal_Iterator {
private:
    Fractal_Template m_base;
    std::vector<Fractal_Element> m_levels;
    size_t m_currentLevel;
    std::vector<Line> m_statics; // Shared by all Fractal_Elements in m_levels

    void IterateTo(size_t level);
    void IterateToInfinity();
public:
    Fractal_Iterator();
    ~Fractal_Iterator();

    void Draw(sf::RenderTarget& target, bool drawPrevious);
    void SetBase(Fractal_Template newBase);
    void SetLevel(size_t level);
};

#endif // FRACTAL_ITERATOR_H

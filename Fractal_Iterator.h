#ifndef FRACTAL_ITERATOR_H
#define FRACTAL_ITERATOR_H

#include "Fractal_Element.h"

class Fractal_Iterator {
private:
    std::vector<Fractal_Element> m_levels;
    size_t m_currentLevel;

    void IterateTo(size_t level);
public:
    Fractal_Iterator();
    ~Fractal_Iterator();

    void Draw(sf::RenderWindow& window);
    void SetBase(Fractal_Element newBase);
    void SetLevel(size_t level);
};

#endif // FRACTAL_ITERATOR_H

#ifndef FRACTAL_ITERATOR_H
#define FRACTAL_ITERATOR_H

#include "Fractal_Element.h"

class Fractal_Iterator {
private:
    sf::RenderWindow* m_window;

    std::vector<Fractal_Element> m_levels;
    size_t m_currentLevel;

public:
    Fractal_Iterator(sf::RenderWindow* window);
    ~Fractal_Iterator();

    void Draw();
    void SetBase(Fractal_Element newBase);
    void SetLevel(size_t level);

    void IterateTo(size_t level);
};

#endif // FRACTAL_ITERATOR_H

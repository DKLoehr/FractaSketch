#ifndef ITER_WINDOW_H
#define ITER_WINDOW_H

#include "gui/Button.h"
#include "Fractal_Iterator.h"

class Iter_Window {
private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;

    Fractal_Iterator m_iterator;
    std::vector<GUI_Element*> m_elements;

    size_t m_currentLevel;

public:
    Iter_Window(sf::RenderWindow& window, sf::Font& font);
    ~Iter_Window();

    void HandleEvents();
    void Draw();

    void StartNewIteration(Fractal_Element base);
    void UpdateLevel(size_t newLevel);
};

#endif // ITER_WINDOW_H

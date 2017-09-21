#ifndef ITER_WINDOW_H
#define ITER_WINDOW_H

#include "gui/GUI_Element.h"
#include "gui/text.h"
#include "gui/checkbox.h"
#include "Fractal_Iterator.h"

class Iter_Window {
private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;

    Fractal_Iterator m_iterator;
    InputBox m_input;
    InputBox m_success;
    Checkbox m_drawPrevious;
    std::vector<GUI_Element*> m_elements;

    size_t m_currentLevel;

    void SaveImage();

public:
    Iter_Window(sf::RenderWindow& window, sf::Font& font);
    ~Iter_Window();

    void HandleEvents();
    void Draw();

    void StartNewIteration(Fractal_Template base);
    void UpdateLevel(size_t newLevel);
};

#endif // ITER_WINDOW_H

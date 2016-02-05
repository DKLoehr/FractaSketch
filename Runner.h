#ifndef RUNNER_H
#define RUNNER_H

#include "gui/button.h"
#include "grid.h"
#include "Iter_Window.h"

class Runner {
private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;
    Iter_Window m_iter_window;

    Fractal_Element m_base;
    Line::line_type m_currentLine;

    std::vector<GUI_Element*> m_elements;

    //TODO: Never actually use names, so just stick all in m_elements
    // Line type selection
    Button line_topRight; // 0
    Button line_botRight; // 1
    Button line_topLeft;  // 2
    Button line_botLeft;  // 3
    Button line_static;   // 4
    Button line_hidden;   // 5

    // Grid type selection
    Button grid_none;     // 6
    Button grid_square;   // 7
    Button grid_hex;      // 8

    // The button to start drawing the fractal
    Button draw_button;   // 9

    // Button to clear the element
    Button clear_button;  // 10

    // The grid itself
    Grid m_grid;

    bool m_drawingLine;
    Line m_line;

public:
    Runner(sf::RenderWindow& window, sf::RenderWindow& iter_window, sf::Font& font);
    ~Runner();

    void HandleEvents();
    void Draw();
};

#endif // RUNNER_H

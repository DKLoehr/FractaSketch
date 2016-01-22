#include "../constants.h"
#include "button.h"
#include "checkbox.h"
#include "text.h"
#include "../grid.h"
#include "../line.h"

// This type is returned in case the event caused
// something outside the GUI to change
enum event_result {
    et_none = 0,
    et_lineChange = 1,  // The line type was changed
    et_setLine = 2,     // The user clicked on the graph
    et_mouseMoved = 3,  // The mouse moved
    et_draw = 4         // The user hit the "draw" button
};

class GUI {

private:
    sf::RenderWindow* m_window;
    sf::Font* m_inFont;
    std::vector<GUI_Element*> elements;

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

    // The grid itself
    Grid m_grid;

public:
    GUI(sf::RenderWindow* window, sf::Font* inFont);
    ~GUI();

    void Draw();
    sf::Vector2f SnapToGrid(sf::Vector2f point);
    event_result HandleEvent(sf::Event event);

    Line::line_type GetLineButton(); // Returns the index of the active line type button
};

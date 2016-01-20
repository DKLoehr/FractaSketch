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
    et_mouseMoved = 3   // The mouse moved
};

class GUI {

private:
    sf::RenderWindow* m_window;
    sf::Font* m_inFont;
    std::vector<GUI_Element*> elements;

    // Line type selection
    Button line_topRight;
    Button line_botRight;
    Button line_topLeft;
    Button line_botLeft;
    Button line_static;
    Button line_hidden;

    // Grid type selection
    Button grid_none;
    Button grid_square;
    Button grid_hex;

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

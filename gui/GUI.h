#include "../constants.h"
#include "button.h"
#include "checkbox.h"
#include "text.h"
#include "../grid.h"

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
    Checkbox grid_none;
    Checkbox grid_square;
    Checkbox grid_hex;

    // The grid itself
    Grid m_grid;

public:
    GUI(sf::RenderWindow* window, sf::Font* inFont);
    ~GUI();

    void Draw();
    sf::Vector2f SnapToGrid(sf::Vector2f point);
};

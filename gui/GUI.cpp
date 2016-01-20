#include "gui.h"

GUI::GUI(sf::RenderWindow* window, sf::Font* inFont):
    m_window(window),
    m_inFont(inFont),
    elements(0),
    line_topRight(window, inFont, 5, 5, 100, 15, "TopLeft"),
    line_botRight(window, inFont, 110, 5, 100, 15, "BotRight"),
    line_topLeft(window, inFont, 215, 5, 100, 15, "TopLeft"),
    line_botLeft(window, inFont, 320, 5, 100, 15, "BotLeft"),
    line_static(window, inFont, 425, 5, 100, 15, "Static"),
    line_hidden(window, inFont, 530, 5, 100, 15, "Hidden"),
    grid_none(window, inFont, 635, 3, "None", false),
    grid_square(window, inFont, 740, 3, "Square", true),
    grid_hex(window, inFont, 845, 3, "Hex", false),
    m_grid(window, sf::Vector2f(0, GUI_HEIGHT_OFFSET), sf::Vector2f(window->getSize()), Grid::gt_square)
{
    elements.push_back(&line_topRight);
    elements.push_back(&line_botRight);
    elements.push_back(&line_topLeft);
    elements.push_back(&line_botLeft);
    elements.push_back(&line_static);
    elements.push_back(&line_hidden);
    elements.push_back(&grid_none);
    elements.push_back(&grid_square);
    elements.push_back(&grid_hex);
}

GUI::~GUI() {

}

void GUI::Draw() {
    std::vector<GUI_Element*>::iterator it;
    for(it = elements.begin(); it != elements.end(); it++)
        (*it)->Draw();
    m_grid.Draw();
}

sf::Vector2f GUI::SnapToGrid(sf::Vector2f point) {
    return m_grid.SnapToNearest(point);
}

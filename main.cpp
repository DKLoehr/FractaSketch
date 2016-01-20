#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

#include "gui/GUI.h"

int main() {
    sf::Font inFont;
    #ifdef __APPLE__
    if(!inFont.loadFromFile(resourcePath() + "VeraMono.ttf"))
        return -1;
    #else
    if(!inFont.loadFromFile("VeraMono.ttf"))
        return -1;
    #endif

    sf::RenderWindow window(sf::VideoMode(1200, 724), "FractaSketch", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(0, 0));

    GUI gui(&window, &inFont);

    sf::Vector2f start = gui.SnapToGrid(sf::Vector2f(400, 400)),
                 finish = gui.SnapToGrid(sf::Vector2f(400, 600));

    Line line(&window, Line::lt_topRight, start, finish);
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            event_result result = gui.HandleEvent(event);
            switch (result) {
            case et_mouseMoved:
                line.SetPosition(start, gui.SnapToGrid(sf::Vector2f(sf::Mouse::getPosition(window))));
                break;
            case et_lineChange:
                line.SetType(gui.GetLineButton());
                break;
            case et_setLine:
                break;
            default:
                break;
            }
        }
        window.clear(sf::Color::White);
        line.Draw(false);
        gui.Draw();
        window.display();
    }
    return 0;
}

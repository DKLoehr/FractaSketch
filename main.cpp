#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

#include "Fractal_Iterator.h"
#include "Runner.h"

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

    sf::RenderWindow iter_window;
    Runner run(window, iter_window, inFont);

    while(window.isOpen()) {
        run.HandleEvents();
        run.Draw();
    }
    iter_window.close();
    return 0;
}

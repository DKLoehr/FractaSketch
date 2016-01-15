#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif
#include "gui/button.h"
#include "gui/checkbox.h"
#include "gui/text.h"

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

    while(window.isOpen()) {

    }
    return 0;
}

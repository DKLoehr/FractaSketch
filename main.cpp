#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

#include "Fractal_Iterator.h"
#include "Runner.h"
#include "config.h"
#include "logging.h"

int main() {
    logging::OpenLog();

    sf::Font inFont;
    logging::AddToLog("Loading font from VeraMono.ttf ...");
    #ifdef __APPLE__
    if(!inFont.loadFromFile(resourcePath() + "VeraMono.ttf")) {
        logging::AddToLog("Failed to load font file!");
        return -1;
    }
    #else
    if(!inFont.loadFromFile("VeraMono.ttf")) {
        logging::AddToLog("Failed to load font file!");
        return -1;
    }
    #endif
    logging::AddToLog("Font loaded successfully\n");

    logging::AddToLog("Loading config from FractaSketch_config.cfg ...");
    config::load_config();
    logging::AddToLog("Done loading config\n");

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

#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

#include "gui/GUI.h"
#include "Fractal_Element.h"

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
                 finish = gui.SnapToGrid(sf::Vector2f(600, 300));

    Fractal_Element fe1, fe2;

    Line line(Line::lt_topRight, start, finish);
    Line target(Line::lt_botLeft, start, finish);
    Line tri1(Line::lt_topLeft, sf::Vector2f(200,300), sf::Vector2f(200,200));
    Line tri2(Line::lt_topRight, sf::Vector2f(200,200), sf::Vector2f (300, 300));

    fe1.AddLine(tri1);
    fe1.AddLine(tri2);

    Line base(Line::lt_hidden, sf::Vector2f(200,300), sf::Vector2f(300,300));
    Transform t = base.Match(target);//fe1.MatchBase(target);
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            event_result result = gui.HandleEvent(event);
            switch (result) {
            case et_mouseMoved:
                line.SetPosition(start, gui.SnapToGrid(sf::Vector2f(sf::Mouse::getPosition(window))));
                break;
            case et_lineChange:
                target.SetType(gui.GetLineButton());
                break;
            case et_setLine:
                break;
            case et_draw:
                fe2 = fe1.TransformAll(fe1.MatchBase(target));
                //tri1 = tri1.ApplyTransform(t);
                //tri2 = tri2.ApplyTransform(t);
                //base = base.ApplyTransform(t);
                break;
            default:
                break;
            }
        }
        window.clear(sf::Color::White);
        target.Draw(window, false);
        //line.Draw(false);
        //moved.Draw(false);
        base.Draw(window, false);
        tri1.Draw(window, false);
        tri2.Draw(window, false);
        //fe1.Draw(false);
        fe2.Draw(window, false);
        gui.Draw();
        window.display();
    }
    return 0;
}

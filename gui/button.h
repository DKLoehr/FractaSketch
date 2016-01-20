#ifndef BUTTON_H
#define BUTTON_H

#include "GUI_Element.h"

class Button : public GUI_Element
{
public:
    Button(); // Note: this doesn't take a window, and so won't create a useful object
    Button(sf::RenderWindow* window, sf::Font* font, int x, int y, int width, int height, std::string str);

    void SetActive(bool active);

    void SetPosition(sf::Vector2f newPos);
    void SetPosition(double x, double y);

    bool OnEnter(); // Always returns true
    void OnClick(double xP, double yP);
    void OnTextEntered(char n);
    void OnKeyPressed(sf::Keyboard::Key key);
};

#endif //BUTTON_H

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "GUI.h"

class Checkbox : public GUI
{
private:
    //sf::Text m_cap;
    bool m_isToggled;

public:
    Checkbox(); // Note: This does not take a window, so it is useless
    Checkbox(sf::RenderWindow* window, sf::Font* font, int x, int y, std::string cap, bool isToggled);

    void Toggle();

    void SetActive(bool active);

    void SetPosition(sf::Vector2f newPos);
    void SetPosition(double x, double y);

    bool OnEnter(); // Toggles, and returns true
    void OnClick(double xP, double yP); // Returns true if the checkbox was clicked
    void OnTextEntered(char n); // Does nothing
    void OnKeyPressed(sf::Keyboard::Key key);
};

#endif // CHECKBOX_H

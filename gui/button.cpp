#include "button.h"
#include <iostream>

Button::Button(sf::RenderWindow* window, sf::Font* font, int x, int y, int width, int height, std::string str) :
        GUI_Element(window, font, x, y, width, height)
{
    m_text.setString(str);

    m_rectangle.setPosition(x, y);
    m_text.setPosition(x, y - 2);
    SetActive(false);
}

Button::Button() {

}

void Button::SetActive(bool active) {
    isActive = active;
    DrawWhite();
    if(isActive) {
        SetOutlineColor(sf::Color::Green);
    } else {
        SetOutlineColor(sf::Color::Black);
    }
    Draw();
}

void Button::SetPosition(sf::Vector2f newPos) {
    SetPosition(newPos.x, newPos.y);
}

void Button::SetPosition(double x, double y) {
    m_rectangle.setPosition(x, y);
    m_text.setPosition(x, y - 2);
}

bool Button::OnEnter() {
    return true;
}

void Button::OnClick(double xP, double yP) {
    return;
}

void Button::OnTextEntered(char n) {
    return;
}

void Button::OnKeyPressed(sf::Keyboard::Key key) {
    return;
}

#include "button.h"
#include <iostream>

Button::Button() {

}

Button::Button(sf::RenderWindow* window, sf::Font* font, int x, int y, int width, int height, std::string str) :
        GUI(window, font, x, y, width, height)
{
    m_text.setString(str);

    m_rectangle.setPosition(x, y);
    m_text.setPosition(x, y - 2);
}

void Button::SetActive(bool active) {
    isActive = active;
    DrawWhite();
    if(isActive) {
        m_rectangle.setFillColor(sf::Color::White);
    } else {
        m_rectangle.setFillColor(sf::Color(150, 150, 150));
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

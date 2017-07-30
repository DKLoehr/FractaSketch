#include "checkbox.h"

Checkbox::Checkbox() {

}

Checkbox::Checkbox(sf::RenderWindow* window, sf::Font* font, int x, int y, std::string cap, bool isToggled)
    : GUI_Element(window, font, x, y, 11, 11)
{
    m_isToggled = !isToggled;
    Toggle(); // Toggle so we update our string

    m_cap.setString(cap);

    m_rectangle.setPosition(x + cap.length() * 10, y + 5);
    m_text.setPosition(x + cap.length() * 10 + 1, y);
    m_cap.setPosition(x, y);
}

void Checkbox::Toggle() {
    m_isToggled = !m_isToggled;
    if(m_isToggled)
        m_text.setString("x");
    else
        m_text.setString("");
}

void Checkbox::SetActive(bool active) {
    isActive = active;
    DrawWhite();
    if(isActive) {
        m_rectangle.setFillColor(sf::Color::White);
    } else {
        m_rectangle.setFillColor(sf::Color(150, 150, 150));
    }
    Draw();
}

void Checkbox::SetPosition(sf::Vector2f newPos) {
    SetPosition(newPos.x, newPos.y);
}

void Checkbox::SetPosition(double x, double y) {
    std::string str = m_cap.getString();
    m_rectangle.setPosition(x + str.length() * 10, y + 5);
    m_text.setPosition(x + str.length() * 10 + 1, y);
    m_cap.setPosition(x, y);
}

bool Checkbox::OnEnter() {
    Toggle();
    return true;
}

void Checkbox::OnClick(double xP, double yP) {
    Toggle();
    (void)xP;
    (void)yP;
    return;
}

void Checkbox::OnTextEntered(char n) {
    (void)n;
    return;
}

void Checkbox::OnKeyPressed(sf::Keyboard::Key key) {
    (void)key;
    return;
}

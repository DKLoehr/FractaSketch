#include "GUI.h"
#include <iostream>

GUI::GUI()
{

}

GUI::GUI(sf::RenderWindow* window, sf::Font* font, double x, double y, double width, double height) :
    m_w(window),
    m_f(font),
    m_position(x, y),
    m_size(width, height),
    m_wSize(window->getSize()),
    m_text("", *font),
    m_cap("", *font),
    m_rectangle(sf::Vector2f(width, height))
{
    m_text.setColor(sf::Color::Black);
    m_text.setCharacterSize(15);

    m_cap.setColor(sf::Color::Black);
    m_cap.setCharacterSize(15);

    m_rectangle.setOutlineThickness(2);
    m_rectangle.setOutlineColor(sf::Color::Black);
    m_rectangle.setFillColor(sf::Color::White);

    m_cap.setPosition(x, y - 2);
    m_rectangle.setPosition(x, y);
    m_text.setPosition(x, y - 2);
}

bool GUI::GetActive() {
    return isActive;
}

void GUI::SetBoxColor(sf::Color c) {
    m_rectangle.setFillColor(c);
}

void GUI::SetOutlineColor(sf::Color c) {
    m_rectangle.setOutlineColor(c);
}

sf::Color GUI::GetBoxColor() {
    return m_rectangle.getFillColor();
}

sf::Color GUI::GetOutlineColor() {
    return m_rectangle.getOutlineColor();
}

bool GUI::IsClicked(double xP, double yP) {
    double xScale = m_w->getSize().x / m_wSize.x, yScale = m_w->getSize().y / m_wSize.y;
    int cap = (((std::string)m_cap.getString()).length() + 1) * 10;

    if(((m_position.x - 3) * xScale < xP) && (xP < (m_position.x + m_size.x + cap + 2) * xScale) &&
       ((m_position.y - 3) * yScale < yP) && (yP < (m_position.y + m_size.y + 6) * yScale))
        return true;
    else
        return false;
}

sf::Vector2f GUI::GetPosition() {
    return m_position;
}

sf::Vector2f GUI::GetSize() {
    return m_size;
}

void GUI::SetText(std::string str) {
    m_text.setString(str);
}

std::string GUI::GetText() {
    return m_text.getString();
}

std::string GUI::GetCap() {
    return m_cap.getString();
}

void GUI::Draw() {
    m_w->draw(m_rectangle);
    m_w->draw(m_text);
    m_w->draw(m_cap);
}

void GUI::DrawWhite() {
    auto whiteRect = m_rectangle;
    whiteRect.setPosition(m_position - sf::Vector2f(1, 1));
    whiteRect.setSize(m_size + sf::Vector2f(((std::string)m_cap.getString()).length() * 10 + 2, 2));
    whiteRect.setFillColor(sf::Color::White);
    whiteRect.setOutlineColor(sf::Color::White);
    m_w->draw(whiteRect);
}

#include "GUI_Element.h"

GUI_Element::GUI_Element() {}

GUI_Element::GUI_Element(sf::RenderWindow* window, sf::Font* font, double x, double y, double width, double height) :
    isActive(false),
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

GUI_Element::~GUI_Element() {

}

bool GUI_Element::GetActive() {
    return isActive;
}

void GUI_Element::SetBoxColor(sf::Color c) {
    m_rectangle.setFillColor(c);
}

void GUI_Element::SetOutlineColor(sf::Color c) {
    m_rectangle.setOutlineColor(c);
}

sf::Color GUI_Element::GetBoxColor() {
    return m_rectangle.getFillColor();
}

sf::Color GUI_Element::GetOutlineColor() {
    return m_rectangle.getOutlineColor();
}

bool GUI_Element::IsClicked(double xP, double yP) {
    double xScale = m_w->getSize().x / m_wSize.x, yScale = m_w->getSize().y / m_wSize.y;
    int cap = (((std::string)m_cap.getString()).length() + 1) * 10;

    if(((m_position.x - 3) * xScale < xP) && (xP < (m_position.x + m_size.x + cap + 2) * xScale) &&
       ((m_position.y - 3) * yScale < yP) && (yP < (m_position.y + m_size.y + 6) * yScale))
        return true;
    else
        return false;
}

sf::Vector2f GUI_Element::GetPosition() {
    return m_position;
}

sf::Vector2f GUI_Element::GetSize() {
    return m_size;
}

void GUI_Element::SetText(std::string str) {
    m_text.setString(str);
}

std::string GUI_Element::GetText() {
    return m_text.getString();
}

std::string GUI_Element::GetCap() {
    return m_cap.getString();
}

void GUI_Element::Draw() {
    m_w->draw(m_rectangle);
    m_w->draw(m_text);
    m_w->draw(m_cap);
}

void GUI_Element::DrawWhite() {
    auto whiteRect = m_rectangle;
    whiteRect.setPosition(m_position - sf::Vector2f(1, 1));
    whiteRect.setSize(m_size + sf::Vector2f(((std::string)m_cap.getString()).length() * 10 + 2, 2));
    whiteRect.setFillColor(sf::Color::White);
    whiteRect.setOutlineColor(sf::Color::White);
    m_w->draw(whiteRect);
}

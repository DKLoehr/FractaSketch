#include <SFML/Graphics.hpp>
#include <string>
#include "text.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

InputBox::InputBox() {

}

InputBox::InputBox(sf::RenderWindow* window, sf::Font* font, int x, int y, int width, int height,
                   std::string cap):
    GUI(window, font, x, y, width, height)
{
    m_cursorPos = 0;
    m_stringPos = 0;
    m_cursor = sf::RectangleShape(sf::Vector2f(1, m_rectangle.getSize().y));
    m_cursor.setOutlineColor(sf::Color::Black);
    m_cursor.setFillColor(sf::Color::Black);

    m_start = std::clock();
    m_drawCursor = true;

    m_cap.setString(cap);

    m_rectangle.setOutlineColor(sf::Color(100,100,100));
    m_rectangle.setSize(m_rectangle.getSize() - sf::Vector2f((int)m_rectangle.getSize().x % 9, 0));

    m_cap.setPosition(x, y - 2);
    m_rectangle.setPosition(x + cap.length() * 10, y);
    m_text.setPosition(x + cap.length() * 10, y - 2);

    m_cursor.setPosition(m_rectangle.getPosition() + sf::Vector2f(1, 0));
};


bool InputBox::IsValid(char n) {
    if(n == 8 || n == 32 || n == 33 || (n >= 40 && n <= 57) || (n >= 65 && n <= 90) || n == 94 ||
       (n >= 97 && n <= 122) || n == 127)
        return true;
    else
        return false;
}

void InputBox::SetActive(bool active) {
    isActive = active;
    if(isActive) {
        m_rectangle.setFillColor(sf::Color::White);
    } else {
        m_rectangle.setFillColor(sf::Color(150, 150, 150));
    }
}

void InputBox::SetPosition(sf::Vector2f newPos) {
    SetPosition(newPos.x, newPos.y);
}

void InputBox::SetPosition(double x, double y) {
    std::string cap = m_cap.getString();
    m_cap.setPosition(x, y - 2);
    m_rectangle.setPosition(x + cap.length() * 10, y);
    m_text.setPosition(x + cap.length() * 10, y - 2);
}

bool InputBox::OnEnter() {
    return false;
}

void InputBox::OnClick(double xP, double yP) {
    SetCursor((int)((xP - m_rectangle.getPosition().x) / 9 + .5)); ///TODO: Add in scaling properly
}

void InputBox::SetCursor(int newCursorPos) {
    int origPos = m_cursorPos;
    m_cursorPos = newCursorPos;
    if(m_cursorPos < 0)
        m_cursorPos = 0;
    if(m_cursorPos > ((std::string)m_text.getString()).length())
        m_cursorPos = ((std::string)m_text.getString()).length();
    if(m_cursorPos * 9 > m_rectangle.getSize().x)
        m_cursorPos =(m_rectangle.getSize().x + 1) / 9;

    m_cursor.setPosition(m_rectangle.getPosition() + sf::Vector2f(m_cursorPos * 9, 0));
    if(((std::string)m_text.getString()).length() < m_rectangle.getSize().x / 9) {
        m_stringPos = m_cursorPos;
    } else {
        m_stringPos = newCursorPos + m_stringPos - origPos;
    }
    if(m_stringPos < 0)
        m_stringPos = 0;
    if(m_stringPos > ((std::string)m_text.getString()).length())
        m_stringPos = ((std::string)m_text.getString()).length();
    }

void InputBox::OnTextEntered(char n) {
    EnterText(n);
}

void InputBox::EnterText(char n) {
    if(IsValid(n)) { // n is a valid character
        std::string temp = m_text.getString();
        if(n != 8) { // Some character
            m_text.setString(temp.substr(0, m_stringPos) + n + temp.substr(m_stringPos, temp.length()));
            SetCursor(m_cursorPos + 1);
        } else if(n == 8) { // Backspace
            if(m_stringPos > 0)
                m_text.setString(temp.substr(0, m_stringPos - 1) + temp.substr(m_stringPos, temp.length()));
            if(((std::string)m_text.getString()).length() * 9 <= m_rectangle.getSize().x)
                SetCursor(m_cursorPos - 1);
            else
                SetCursor(m_cursorPos);
        }
    }
}

void InputBox::OnKeyPressed(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Right)
        SetCursor(m_cursorPos + 1);
    if(key == sf::Keyboard::Left)
        SetCursor(m_cursorPos - 1);
}

void InputBox::Draw() {
    m_w->draw(m_rectangle);
    std::string str = m_text.getString();
    if(str.length() * 9 > m_rectangle.getSize().x + 1) {
        std::string truncStr;
        truncStr = str.substr(m_stringPos - m_cursorPos, m_rectangle.getSize().x / 9);
        m_text.setString(truncStr);
    }
    m_w->draw(m_text);
    m_text.setString(str);
    m_w->draw(m_cap);
    if(isActive) {
        if((std::clock() - m_start)/ (double)CLOCKS_PER_SEC > .5) {
            m_drawCursor = !m_drawCursor;
            m_start = std::clock();
        }
        if(m_drawCursor)
            m_w->draw(m_cursor);
    }
}

double InputBox::GetStringAsDouble() {
    return atof(((std::string)m_text.getString()).c_str());
}

sf::Vector2f InputBox::GetStringAsVector() {
    std::string str = m_text.getString();
    if(str.find('(') != std::string::npos)
        str = str.substr(1, std::string::npos);
    if(str.find(')') != std::string::npos)
        str = str.substr(0, str.length() - 1);
    std::string xStr = str.substr(0, str.find(','));
    std::string yStr = str.substr(str.find(',') +  1, str.length());
    return sf::Vector2f(atof(xStr.c_str()), atof(yStr.c_str()));
}

std::string InputBox::GetOrderedPairElement(bool first) {
    std::string str = m_text.getString();
    if(str.find('(') != std::string::npos)
        str = str.substr(1, std::string::npos);
    if(str.find(')') != std::string::npos)
        str = str.substr(0, str.length() - 1);
    std::string xStr = str.substr(0, str.find(','));
    std::string yStr = str.substr(str.find(',') +  1, str.length());
    if(first)
        return xStr;
    else
        return yStr;
}

#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "GUI_Element.h"

class InputBox : public GUI_Element
{
private:
    int m_cursorPos;
    int m_stringPos;
    sf::RectangleShape m_cursor;

    std::clock_t m_start;
    bool m_drawCursor;

    bool IsValid(char n);

    void SetCursor(int newCursorPos);
public:
    InputBox(sf::RenderWindow& window, sf::Font& font, int x, int y, int charWidth, int charHeight, std::string cap = "");

    void SetActive(bool active);

    void SetPosition(sf::Vector2f newPos);
    void SetPosition(double x, double y);

    bool OnEnter(); // Does nothing
    void OnClick(double xP, double yP); // Sets cursor
    void OnTextEntered(char n); // Adds text to string
    void OnKeyPressed(sf::Keyboard::Key key);
    void EnterText(char n); // Same as OnTextEntered

    void Draw();

    double GetStringAsDouble(); // Only call if you know the string is just a single number
    sf::Vector2f GetStringAsVector(); // Only call if you know the string is of the form "(#, #)"
    std::string GetOrderedPairElement(bool first); // Also only call if in the form (#1, #2); if first is true, returns #1, else, returns #2, both as strings
};

#endif //INPUT_BOX_H

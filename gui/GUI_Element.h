#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Runner;

class GUI_Element
{
protected:
    bool isActive;

    sf::RenderWindow* m_w;
    sf::Font* m_f;

    sf::Vector2f m_position; // x and y position
    sf::Vector2f m_size;     // Width and heights
    sf::Vector2f m_wSize;    // Initial width and height of the window (for dealing with resizing)

    sf::Text m_text;
    sf::Text m_cap;
    sf::RectangleShape m_rectangle;
public:
    GUI_Element();
    GUI_Element(sf::RenderWindow* window, sf::Font* font, double x, double y, double width, double height);

    virtual ~GUI_Element();

    void SetBoxColor(sf::Color c);
    void SetOutlineColor(sf::Color c);
    sf::Color GetBoxColor();
    sf::Color GetOutlineColor();

    virtual void SetActive(bool active) = 0;
    bool GetActive(); // Returns isActive

    virtual void SetPosition(sf::Vector2f newPos) = 0;
    virtual void SetPosition(double x, double y) = 0;

    virtual bool OnEnter() = 0;
    virtual void OnClick(double xP, double yP) = 0; // Stuff to do if the gui element was clicked
    bool IsClicked(double xP, double yP); // Returns true if the gui element was clicked
    virtual void OnTextEntered(char n) = 0;
    virtual void OnKeyPressed(sf::Keyboard::Key key) = 0;

    sf::Vector2f GetPosition();
    sf::Vector2f GetSize();

    void SetText(std::string str);
    std::string GetText();
    std::string GetCap();

    virtual void Draw();
    virtual void DrawWhite();
};

#endif // GUI_H

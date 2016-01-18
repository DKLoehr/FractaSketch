#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include "constants.h"

// The first four types refer to the location of the arrow
// on horizontal line in the positive x direction
enum line_type {
    lt_base = 0,    // The base line on the template
    lt_topRight = 1,
    lt_botRight = 2,
    lt_topLeft = 3,
    lt_botLeft = 4,
    lt_static = 5, // Not replaced during iterations
    lt_hidden = 6 // Neither shown nor replaced during iterations
};

class Line
{
private:
    sf::RenderWindow* m_window;
    line_type m_type;
    sf::Vector2f m_start;
    sf::Vector2f m_finish;

    sf::VertexArray m_body; // The thing that is actually drawn

    void ConstructBody(); // Fills out body based on m_type
public:
    Line(sf::RenderWindow* window, line_type type, sf::Vector2f start, sf::Vector2f finish);
    ~Line();

    void Draw(bool simple);
    line_type GetType();
    void SetType(line_type newType);
    void SetPosition(sf::Vector2f start, sf::Vector2f finish);

};



#endif // LINE_H

#include "line.h"
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846264338328
#endif // M_PI
#include <iostream>

Line::Line(sf::RenderWindow* window, line_type type, sf::Vector2f start, sf::Vector2f finish):
    m_window(window),
    m_type(type),
    m_start(start),
    m_finish(finish),
    m_body(sf::Lines,0)
{
    ConstructBody();
}

Line::~Line() {

}

void Line::Draw(bool simple) {
    if(simple) { // Just draw a straight line
        if(m_type >= 5) { // A hidden or base line
            return; // Don't draw
        }
        sf::Vertex simpleLine[] = {sf::Vertex(m_start, sf::Color::Black),
                                   sf::Vertex(m_finish, sf::Color::Black)};
        m_window->draw(simpleLine, 2, sf::Lines);
    } else {
        m_window->draw(m_body);
    }
}

void Line::ConstructBody() {
    m_body.clear();
    m_body.setPrimitiveType(sf::Lines);
    sf::Color color = sf::Color::Black;

    sf::Vector2f dist = m_finish - m_start;
    double length = sqrt(dist.x * dist.x + dist.y * dist.y);
    dist /= (float)length;
    sf::Vector2f arrow, loc, dot; // For hidden and base lines
    int numDots = -1;

    if(m_type != lt_base && m_type != lt_hidden) { // No dots
        m_body.append(sf::Vertex(m_start, color));
        m_body.append(sf::Vertex(m_finish, color));
    }

    switch(m_type) {
    case lt_topRight:
        m_body.append(sf::Vertex(m_finish, color));
        m_body.append(sf::Vertex(m_finish - sf::Vector2f(dist.x, dist.y) * (float)LINE_ARROW_LENGTH
                                          + sf::Vector2f(dist.y*LINE_ARROW_LENGTH, dist.x*-LINE_ARROW_HEIGHT), color));
        return;
    case lt_botRight:
        m_body.append(sf::Vertex(m_finish, color));
        m_body.append(sf::Vertex(m_finish - sf::Vector2f(dist.x, dist.y) * (float)LINE_ARROW_LENGTH
                             + sf::Vector2f(dist.y*-LINE_ARROW_LENGTH, dist.x*LINE_ARROW_HEIGHT), color));
        return;
    case lt_topLeft:
        m_body.append(sf::Vertex(m_start, color));
        m_body.append(sf::Vertex(m_start + sf::Vector2f(dist.x, dist.y) * (float)LINE_ARROW_LENGTH
                                         + sf::Vector2f(dist.y*LINE_ARROW_LENGTH, dist.x*-LINE_ARROW_HEIGHT), color));
        return;
    case lt_botLeft:
        m_body.append(sf::Vertex(m_start, color));
        m_body.append(sf::Vertex(m_start + sf::Vector2f(dist.x, dist.y) * (float)LINE_ARROW_LENGTH
                                         + sf::Vector2f(dist.y*-LINE_ARROW_LENGTH, dist.x*LINE_ARROW_HEIGHT), color));
        return;
    case lt_base:
        arrow = m_finish - sf::Vector2f(dist.x, dist.y) * (float)LINE_ARROW_LENGTH
                                  + sf::Vector2f(dist.y*LINE_ARROW_LENGTH, dist.x*-LINE_ARROW_HEIGHT);
        loc = m_start;
        dot = dist * (float)LINE_DOT_SIZE;
        numDots = length / LINE_DOT_SIZE / 2;
        for(int iii = 0; iii < numDots; iii++) { // Draw the dots along the line
            m_body.append(sf::Vertex(loc, color));
            m_body.append(sf::Vertex(loc + dot, color));
            loc += dot * (float)2.0;
        }
        m_body.append(sf::Vertex(loc, color));
        m_body.append(sf::Vertex(m_finish, color));

        loc = m_finish;
        dot = (arrow - m_finish);
        dot *= (float)(LINE_DOT_SIZE / sqrt(dot.x*dot.x + dot.y*dot.y));
        numDots = sqrt(LINE_ARROW_HEIGHT*LINE_ARROW_HEIGHT + LINE_ARROW_LENGTH*LINE_ARROW_LENGTH) / LINE_DOT_SIZE / 2; // TODO: Don't recalculate this every time
        for(int iii = 0; iii < numDots; iii++) { // Draw the dots along the arrow
            m_body.append(sf::Vertex(loc, color));
            m_body.append(sf::Vertex(loc + dot, color));
            loc += dot * (float)2.0;
        }
        m_body.append(sf::Vertex(loc, color));
        m_body.append(sf::Vertex(arrow, color));
        break;
    case lt_hidden:
        m_body.setPrimitiveType(sf::Points);
        loc = m_start;
        dot = sf::Vector2f(dist.y, -dist.x) * (float)LINE_DOT_DIST;
        numDots = length / LINE_DOT_DIST / 2;
        for(int iii = 0; iii < numDots; iii++) {
            m_body.append(sf::Vertex(loc - dot, color));
            loc += dist * (float)LINE_DOT_DIST;
            m_body.append(sf::Vertex(loc, color));
            loc += dist * (float)LINE_DOT_DIST;
            m_body.append(sf::Vertex(loc + dot, color));
        }
        break;
    default: // Solid line, no arrow
       return;
    }
}

Line::line_type Line::GetType() {
    return m_type;
}

void Line::SetType(line_type newType) {
    m_type = newType;
    ConstructBody();
}

void Line::SetPosition(sf::Vector2f start, sf::Vector2f finish) {
    m_start = start;
    m_finish = finish;

    ConstructBody();
}

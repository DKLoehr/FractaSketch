#include "line.h"
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846264338328
#endif // M_PI

Line::Line(line_type type, sf::Vector2f start, sf::Vector2f finish):
    m_type(type),
    m_start(start),
    m_finish(finish),
    m_body(sf::Lines,0)
{
    ConstructBody();
}

Line::~Line() {

}

double Line::Length() const {
    sf::Vector2f dist = m_finish - m_start;
    return sqrt(dist.x*dist.x + dist.y*dist.y);
}

sf::Vector2f Line::GetStart() const {
    return m_start;
};

sf::Vector2f Line::GetFinish() const {
    return m_finish;
};

sf::Vector2f Line::FromOrigin() const {
    return m_finish - m_start;
};

void Line::Draw(sf::RenderWindow& window, bool simple) const {
    if(simple) { // Just draw a straight line
        if(m_type == 0 || m_type == 6) { // A hidden or base line
            return; // Don't draw
        }
        sf::Vertex simpleLine[] = {sf::Vertex(m_start, sf::Color::Black),
                                   sf::Vertex(m_finish, sf::Color::Black)};
        window.draw(simpleLine, 2, sf::Lines);
    } else {
        window.draw(m_body);
    }
}

void Line::ConstructBody() {
    m_body.clear();
    m_body.setPrimitiveType(sf::Lines);
    sf::Color color = sf::Color::Black;

    if(m_start == m_finish) {
        m_body.append(sf::Vertex(m_start, color));
        m_body.append(sf::Vertex(m_start, color));
        return;
    }

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

Line::line_type Line::GetType() const {
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

Transform Line::Match(const Line& base) const {
    sf::Vector2f baseStart = base.GetStart();
    sf::Vector2f baseFinish = base.GetFinish();

    if(base.GetType() == Line::lt_botLeft ||
       base.GetType() == Line::lt_topLeft) {
        baseStart = base.GetFinish();
        baseFinish = base.GetStart();
    }

    sf::Vector2f myDiff = m_finish - m_start,
                 baseDiff = baseFinish - baseStart;

    double scale = base.Length() / Length();

    double theta = atan2(baseDiff.y*myDiff.x - baseDiff.x*myDiff.y, baseDiff.x*myDiff.x + baseDiff.y*myDiff.y);
    sf::Vector2f translate = baseStart - m_start;

    sf::Vector2f reflect_start(0,0),
                 reflect_finish(0,0);
    if(base.GetType() == Line::lt_botRight ||
       base.GetType() == Line::lt_topLeft) {
        reflect_start = baseStart;
        reflect_finish = baseFinish;
    }

    return Transform(scale, theta, m_start, translate, reflect_start, reflect_finish);
}

Line Line::ApplyTransform(Transform t) const {
    sf::Vector2f newStart = m_start - t.origin,
                 newFinish = m_finish - t.origin;

    // Rotations
    newStart = sf::Vector2f(newStart.x*cos(t.theta) - newStart.y*sin(t.theta),
                             newStart.x*sin(t.theta) + newStart.y*cos(t.theta));
    newFinish = sf::Vector2f(newFinish.x*cos(t.theta) - newFinish.y*sin(t.theta),
                             newFinish.x*sin(t.theta) + newFinish.y*cos(t.theta));

    // Dilations
    newStart *= (float)t.scale;
    newFinish *= (float)t.scale;

    // Translations
    newStart += t.origin + t.translate;
    newFinish += t.origin + t.translate;

    Line::line_type newType = m_type;
    if(newType == lt_base)
        newType = lt_topLeft;
    // Reflections, if necessary
    if(t.reflect_start != t.reflect_finish) {
        sf::Vector2f axis = t.reflect_finish - t.reflect_start;
        double axisSquared = axis.x*axis.x + axis.y*axis.y;
        sf::Vector2f P = newStart - t.reflect_start;
        newStart = (float)(2*(P.x*axis.x + P.y*axis.y)/axisSquared) * axis - P + t.reflect_start;
        P = newFinish - t.reflect_start;
        newFinish = (float)(2*(P.x*axis.x + P.y*axis.y)/axisSquared) * axis - P + t.reflect_start;
        if(newType == lt_topRight || newType == lt_topLeft)
            newType = (Line::line_type)(newType + 1);
        else
            newType = (Line::line_type)(newType - 1);
    }

    return Line(newType, newStart, newFinish);
}

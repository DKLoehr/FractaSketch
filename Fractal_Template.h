#ifndef FRACTAL_TEMPLATE_H
#define FRACTAL_TEMPLATE_H

#include "line.h"

class Fractal_Template {
private:
    Line m_baseline;
    // We need to be able to manipulate both the lines and their endpoints, but
    // endpoints correspond to more than one line. Thus for ease of access we
    // track them separately. The relationship is as follows:
    // m_lines[index] is the line from m_points[index] to m_points[index + 1]
    std::vector<Line> m_lines;
    std::vector<sf::Vector2f> m_points;
    size_t m_activeLine;
    size_t m_activePoint;

public:
    Fractal_Template();
    ~Fractal_Template();

    const std::vector<Line>& GetLines() const;

    // Selects a line if there is one close enough to the given position
    void SelectNear(sf::Vector2f clickPos);

    void AddLine(sf::Vector2f endpoint, Line::line_type ltype);
    void RemoveLine(size_t index);
    void RemovePoint(size_t index);
    void SplitLine(); // Splits the active line into to lines of half length
    void TranslateAll(sf::Vector2f displacement);
    void MovePoint(sf::Vector2f newPos);

    void Draw(sf::RenderWindow& window, bool simple) const;
    void SetBase(sf::Vector2f start, sf::Vector2f finish);
};
#endif // FRACTAL_TEMPLATE_H


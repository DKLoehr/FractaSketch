#ifndef FRACTAL_ELEMENT_H
#define FRACTAL_ELEMENT_H

#include "line.h"

class Fractal_Element {
private:
    sf::RenderWindow* m_window;

    Line m_baseline;
    std::vector<Line> m_lines;

public:
    Fractal_Element(sf::RenderWindow* window);
    ~Fractal_Element();

    void AddLine(Line newLine);
    Transform MatchBase(const Line& base);

    Fractal_Element TransformAll(Transform t);

    void Draw(bool simple);
};
#endif // FRACTAL_ELEMENT_H

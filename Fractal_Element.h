#ifndef FRACTAL_ELEMENT_H
#define FRACTAL_ELEMENT_H

#include "line.h"

class Fractal_Element {
private:
    Line m_baseline;
    std::vector<Line> m_lines;

public:
    Fractal_Element();
    ~Fractal_Element();

    void AddLine(Line newLine);
    const std::vector<Line>& GetLines() const;

    Transform MatchBase(const Line& base) const;
    Fractal_Element TransformAll(Transform t) const;
    Fractal_Element ReplaceAll(const Fractal_Element& target) const;

    void Draw(sf::RenderWindow& window, bool simple) const;

};
#endif // FRACTAL_ELEMENT_H

#ifndef FRACTAL_ELEMENT_H
#define FRACTAL_ELEMENT_H

#include "line.h"
#include "Fractal_Template.h"

class Fractal_Element {
private:
    Line m_baseline;
    std::vector<Line> m_lines;
    // This pointer is shared between all Fractal_Elements for a given Fractal_Iterator
    std::vector<Line>* statics;
    // The place in statics to stop drawing lines. Lines past this point
    // were added by a later, more complicated FE.
    std::vector<Line>::iterator m_statics_end;

    double m_maxLength; // Maximum length of any non-static line in the element
public:
    Fractal_Element(std::vector<Line>* statics);
    ~Fractal_Element();

    void AddLine(Line newLine);
    const std::vector<Line>& GetStatics() const;
    const std::vector<Line>& GetLines() const;

    double GetMaxLength();

    Fractal_Element ReplaceAll(const Fractal_Template& target) const;

    void Draw(sf::RenderWindow& window, bool simple) const;
    void SetBase(sf::Vector2f start, sf::Vector2f finish);

    double BaseLength();

};
#endif // FRACTAL_ELEMENT_H

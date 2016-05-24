#include "Fractal_Template.h"
#include "constants.h"

Fractal_Template::Fractal_Template():
    m_baseline(Line::lt_base, sf::Vector2f(0,0), sf::Vector2f(0,0))
{

}

Fractal_Template::~Fractal_Template() {

}

const std::vector<Line>& Fractal_Template::GetLines() const {
    return m_lines;
}

// Selects a line or point if there is one close enough to the given position
void Fractal_Template::SelectNear(sf::Vector2f clickPos) {
    // Clear previous selections
    if(m_activeLine < m_lines.size())
        m_lines[m_activeLine].SetColor(sf::Color::Black);
    m_activeLine = -1;
    m_activePoint = -1;

    for(auto point_it = m_points.begin(); point_it != m_points.end(); point_it++) {
        sf::Vector2f diff = *point_it - clickPos;
        double dist = sqrt(diff.x * diff.x + diff.y * diff.y);
        if(dist < TEMPLATE_SELECT_DOT_RAD) {
            m_activePoint = point_it - m_points.begin();
            return;
        }
    }

    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        sf::Vector2f finish = line_it->GetFinish(),
                     start = line_it->GetStart();
        sf::Vector2f line_vec = finish - start;
        double line_len = sqrt(line_vec.x * line_vec.x + line_vec.y * line_vec.y);
        double area = fabs((line_vec.y * clickPos.x) - (line_vec.x * clickPos.y) + (finish.x * start.y) - (finish.y * start.x));
        double dist = area / line_len; // Distance from clickPos to the line. Comes from rearranging the formula for a triangle.
        if(dist < TEMPLATE_SELECT_LINE_RAD) {
            m_activeLine = line_it - m_lines.begin();
            m_lines[m_activeLine].SetColor(sf::Color::Red);
            return;
        }
    }
}

void Fractal_Template::AddLine(sf::Vector2f endpoint, Line::line_type ltype) {
    m_lines.push_back(Line(ltype, m_points.back(), endpoint));
    m_points.push_back(endpoint);
}

void Fractal_Template::RemoveLine(size_t index) {
    // TODO: Ensure index is valid
    if(index >= m_lines.size()) {
        //std::cout << "Invalid index in RemoveLine: " << index << "\n";
        return;
    }

    m_lines.erase(m_lines.begin() + index);
    m_points.erase(m_points.begin() + index);

    if(m_points.size() <= 1) { // Too few points to make a line
        m_points.clear();
        SetBase(sf::Vector2f(0,0), sf::Vector2f(0,0));
        return;
    }

    if(index == 0 || index == m_lines.size() - 1) { // Removing the first or last lines
        SetBase(m_points.front(), m_points.back());
    } else { // Somewhere in the middle
        m_lines[index - 1].SetPosition(m_points[index - 1], m_points[index]);
    }
}

void Fractal_Template::RemovePoint(size_t index) {
    if(index == m_points.size() - 1) {
        m_lines.pop_back();
        m_points.pop_back();
        SetBase(m_points.front(), m_points.back());
    }
    else {
        RemoveLine(index);
    }
}

void Fractal_Template::SplitLine() { // Splits the active line into to lines of half length
    if(m_activeLine >= m_lines.size())
        return;

    size_t index = m_activeLine;
    sf::Vector2f midpoint = (m_lines[index].GetStart() + m_lines[index].GetFinish()) / 2.0f;
    m_points.insert(m_points.begin() + (index + 1), midpoint);
    m_lines[index].SetPosition(m_points[index], m_points[index + 1]);
    m_lines.insert(m_lines.begin() + (index + 1), Line(m_lines[index].GetType(), m_points[index + 1], m_points[index + 2]));
}

void Fractal_Template::TranslateAll(sf::Vector2f displacement) {
    for(auto point_it = m_points.begin(); point_it != m_points.end(); point_it++) {
        *point_it += displacement;
    }
    for(size_t iii = 0; iii < m_lines.size(); iii++) {
        m_lines[iii].SetPosition(m_points[iii], m_points[iii + 1]);
    }
}

// Moves the active point to the the given position
void Fractal_Template::MovePoint(sf::Vector2f newPos) {
    if(m_activePoint >= m_points.size())
        return;

    size_t index = m_activePoint;
    m_points[index] = newPos;
    if(index == 0) {
        m_lines[index].SetPosition(m_points[index], m_points[index + 1]);
        SetBase(m_points.front(), m_points.back());
    } else if (index == m_points.size() - 1) {
        m_lines[index - 1].SetPosition(m_points[index - 1], m_points[index]);
        SetBase(m_points.front(), m_points.back());
    } else {
        m_lines[index].SetPosition(m_points[index], m_points[index + 1]);
        m_lines[index - 1].SetPosition(m_points[index - 1], m_points[index]);
    }
}

void Fractal_Template::Draw(sf::RenderWindow& window, bool simple) const {
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        line_it->Draw(window, simple);
    }
    sf::CircleShape point(TEMPLATE_DOT_RAD);
    point.setFillColor(sf::Color::Black); // TODO: Take into account the active point
    point.setOrigin(TEMPLATE_DOT_RAD, TEMPLATE_DOT_RAD); // Position relative to center instead of top-left corner
    for(size_t iii = 0; iii < m_points.size(); iii++) {
        if(iii == m_activePoint)
            point.setFillColor(sf::Color::Red);
        point.setPosition(m_points[iii]);
        window.draw(point);
        if(iii == m_activePoint)
            point.setFillColor(sf::Color::Black);
    }
    m_baseline.Draw(window, simple);
}

void Fractal_Template::SetBase(sf::Vector2f start, sf::Vector2f finish) {
    m_baseline.SetPosition(start, finish);
}

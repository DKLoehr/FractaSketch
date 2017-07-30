#include "Fractal_Template.h"
#include "constants.h"
#include <fstream>
#include "utils.h"

Fractal_Template::Fractal_Template():
    m_baseline(Line::lt_base, sf::Vector2f(0,0), sf::Vector2f(0,0)),
    m_lines(),
    m_points(),
    m_activeLine(-1),
    m_activePoint(-1)
{

}

Fractal_Template::~Fractal_Template() {

}

const std::vector<Line>& Fractal_Template::GetLines() const {
    return m_lines;
}

const Line& Fractal_Template::GetBase() const {
    return m_baseline;
}

void Fractal_Template::OnClick(sf::Vector2f clickPos) {
    size_t oldLine = m_activeLine;
    SelectNear(clickPos);
    if(oldLine == m_activeLine && m_activeLine < m_lines.size())
        SplitLine(m_activeLine);
}

// Selects a line or point if there is one close enough to the given position
void Fractal_Template::SelectNear(sf::Vector2f clickPos) {
    // Clear previous selections
    if(m_activeLine < m_lines.size())
        m_lines[m_activeLine].SetColor(sf::Color::Black);
    m_activeLine = -1;
    m_activePoint = -1;

    // Check to see if we're close enough to a point
    for(auto point_it = m_points.begin(); point_it != m_points.end(); point_it++) {
        sf::Vector2f diff = *point_it - clickPos;
        double dist = sqrt(diff.x * diff.x + diff.y * diff.y);
        if(dist < TEMPLATE_SELECT_DOT_RAD) {
            m_activePoint = point_it - m_points.begin();
            return;
        }
    }

    // If not, check to see if we're close enough to a line
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        sf::Vector2f finish = line_it->GetFinish(),
                     start = line_it->GetStart();
        sf::Vector2f line_vec = finish - start;
        double line_len = sqrt(line_vec.x * line_vec.x + line_vec.y * line_vec.y);

        // We want to be in between the two endpoints in order to select the line
        sf::Vector2f toMidpoint = clickPos - ((start + finish) / 2.0f);
        double distToMidpoint = sqrt(toMidpoint.x * toMidpoint.x + toMidpoint.y * toMidpoint.y);
        if(distToMidpoint > line_len / 2) // We're outside the endpoints
            continue;

        double area = fabs((line_vec.y * clickPos.x) - (line_vec.x * clickPos.y) + (finish.x * start.y) - (finish.y * start.x));
        double dist = area / line_len; // Distance from clickPos to the line. Comes from rearranging the formula for a triangle.
        if(dist < TEMPLATE_SELECT_LINE_RAD) {
            m_activeLine = line_it - m_lines.begin();
            m_lines[m_activeLine].SetColor(sf::Color::Red);
            return;
        }
    }
}

void Fractal_Template::StartAtPoint(sf::Vector2f startPoint) {
    m_points.push_back(startPoint);
}

void Fractal_Template::AddLine(sf::Vector2f endpoint, Line::line_type ltype) {
    m_lines.push_back(Line(ltype, m_points.back(), endpoint));
    m_points.push_back(endpoint);
}

void Fractal_Template::RemoveLine(size_t index) {
    m_lines.erase(m_lines.begin() + index);
    if(index != m_lines.size()) // Erase the start point if it's not the last line
        m_points.erase(m_points.begin() + index);
    else // If it was the last line, erase its endpoint instead
        m_points.pop_back();

    if(m_points.size() <= 1) { // Too few points to make a line
        Clear();
        return;
    }

    if(index == 0 || index == m_lines.size()) { // Removing the first or last lines
        SetBase(m_points.front(), m_points.back());
    } else { // Somewhere in the middle
        m_lines[index - 1].SetPosition(m_points[index - 1], m_points[index]);
    }

    m_activeLine = -1;
}

void Fractal_Template::RemovePoint(size_t index) {
    if(index == m_points.size() - 1) {
        if(m_lines.size() > 0)
            m_lines.pop_back();
        if(m_points.size() > 2) {
            m_points.pop_back();
            SetBase(m_points.front(), m_points.back());
        }
        else {
            Clear();
        }
    }
    else if (index == m_points.size() - 2) {
        m_lines.pop_back();
        if(m_lines.size() == 0) {
            Clear();
            return;
        }
        m_points.erase(m_points.end() - 2);
        m_lines[m_lines.size()-1].SetPosition(m_points[m_points.size()-2], m_points.back());
    }
    else {
        RemoveLine(index);
    }
    m_activePoint = -1;
}

void Fractal_Template::RemoveSelected() {
    if(m_activeLine < m_lines.size())
        RemoveLine(m_activeLine);
    else if(m_activePoint < m_points.size())
        RemovePoint(m_activePoint);
}

void Fractal_Template::ChangeType(Line::line_type newType) {
    if(m_activeLine < m_lines.size())
        m_lines[m_activeLine].SetType(newType);
}

void Fractal_Template::SplitLine(size_t index) { // Splits the active line into to lines of half length
    sf::Vector2f midpoint = (m_lines[index].GetStart() + m_lines[index].GetFinish()) / 2.0f;
    m_points.insert(m_points.begin() + (index + 1), midpoint);
    m_lines[index].SetPosition(m_points[index], m_points[index + 1]);
    m_lines[index].SetColor(sf::Color::Black);
    m_lines.insert(m_lines.begin() + (index + 1), Line(m_lines[index].GetType(), m_points[index + 1], m_points[index + 2]));
    m_activeLine = -1;
    m_activePoint = -1;
}

void Fractal_Template::Translate(sf::Vector2f displacement) {
    if(m_activeLine >= m_lines.size() &&
       m_activePoint >= m_points.size()) // Don't have anything currently active
        TranslateAll(-1.0f * displacement);
}

void Fractal_Template::TranslateAll(sf::Vector2f displacement) {
    for(auto point_it = m_points.begin(); point_it != m_points.end(); point_it++) {
        *point_it += displacement;
    }
    for(size_t iii = 0; iii < m_lines.size(); iii++) {
        m_lines[iii].SetPosition(m_points[iii], m_points[iii + 1]);
    }
    SetBase(m_points.front(), m_points.back());
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

void Fractal_Template::Clear() {
    m_lines.clear();
    m_points.clear();
    m_activeLine = -1;
    m_activePoint = -1;
    SetBase(sf::Vector2f(0,0), sf::Vector2f(0,0));
}

Transform Fractal_Template::MatchBase(const Line& base) const {
    return m_baseline.Match(base);
}

Fractal_Template Fractal_Template::TransformAll(Transform t) const {
    Fractal_Template newFT;
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        Line transformed = line_it->ApplyTransform(t);
        if(line_it == m_lines.begin())
            newFT.StartAtPoint(transformed.GetStart());
        newFT.AddLine(transformed.GetFinish(), transformed.GetType());
    }
    return newFT;
}

void Fractal_Template::Draw(sf::RenderWindow& window, bool simple) const {
    Line::draw_type style = simple ? Line::dt_simple : Line::dt_default;
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        line_it->Draw(window, style);
    }
    sf::CircleShape point(TEMPLATE_DOT_RAD);
    point.setFillColor(sf::Color::Black);
    point.setOrigin(TEMPLATE_DOT_RAD, TEMPLATE_DOT_RAD); // Position relative to center instead of top-left corner
    for(size_t iii = 0; iii < m_points.size(); iii++) {
        if(iii == m_activePoint)
            point.setFillColor(sf::Color::Red);
        point.setPosition(m_points[iii]);
        window.draw(point);
        if(iii == m_activePoint)
            point.setFillColor(sf::Color::Black);
    }
    m_baseline.Draw(window, style);
}

void Fractal_Template::DrawBaseline() {
    if(m_points.size() >= 2)
      SetBase(m_points.front(), m_points.back());
}

void Fractal_Template::SetBase(sf::Vector2f start, sf::Vector2f finish) {
    m_baseline.SetPosition(start, finish);
}

bool Fractal_Template::SaveToFile(std::string filename) {
    std::ofstream outFile;

    filename = GetProperPath(filename);
    if(filename.length() == 0)
        return false;

    if(filename.length() < 4 || filename.substr(filename.length()-4) != ".fsk")
        filename += ".fsk";

    outFile.open(filename);
    if(!outFile.is_open())
        return false;

    if(m_points.size() == 0) {
        outFile.close();
        return true;
    }

    outFile << m_points[0].x << " " << m_points[0].y << "\n";
    for(size_t iii = 0; iii < m_lines.size(); iii++) {
        outFile << (int)(m_lines[iii].GetType()) << " "
                << m_points[iii+1].x << " "
                << m_points[iii+1].y << "\n";
    }

    outFile.close();
    return true;
}

bool Fractal_Template::LoadFromFile(std::string filename) {
    std::ifstream inFile;
    filename = GetProperPath(filename);
    inFile.open(filename);
    if(!inFile.is_open())
        return false;

    Clear();
    int line_type;
    double x, y;

    if(inFile >> x >> y) {
        StartAtPoint(sf::Vector2f(x,y));
    } else if (inFile.fail() || inFile.bad()) {
        inFile.close();
        return false; // Bad input
    } else {
        inFile.close();
        return true; // Empty file
    }

    while(inFile >> line_type >> x >> y) {
        AddLine(sf::Vector2f(x,y), (Line::line_type)line_type);
    }

    if (!inFile.eof()) {
        inFile.close();
        return false; // Bad input
    }

    DrawBaseline();

    inFile.close();
    return true;
}

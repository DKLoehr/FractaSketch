#include "Runner.h"

Runner::Runner(sf::RenderWindow& window, sf::RenderWindow& iter_window, sf::Font& font) :
    m_window(window),
    m_iter_window(iter_window),
    m_font(font),
    m_base(),
    m_iter(m_iter_window),
    m_currentLine(Line::lt_topRight),
    m_elements(0),
    line_topRight(window, font, 5, 5, 100, 15, "TopRight"),
    line_botRight(window, font, 110, 5, 100, 15, "BotRight"),
    line_topLeft(window, font, 215, 5, 100, 15, "TopLeft"),
    line_botLeft(window, font, 320, 5, 100, 15, "BotLeft"),
    line_static(window, font, 425, 5, 100, 15, "Static"),
    line_hidden(window, font, 530, 5, 100, 15, "Hidden"),
    grid_none(window, font, 635, 5, 100, 15, "No Grid"),
    grid_square(window, font, 740, 5, 100, 15, "Square Grid"),
    grid_hex(window, font, 845, 5, 100, 15, "Hex Grid"),
    draw_button(window, font, 950, 5, 100, 15, "Draw"),
    clear_button(window, font, 1055, 5, 100, 15, "Clear"),
    m_grid(window, sf::Vector2f(0, GUI_HEIGHT_OFFSET), sf::Vector2f(m_window.getSize()), Grid::gt_square),
    m_drawingLine(false),
    m_line(m_currentLine, sf::Vector2f(0,0), sf::Vector2f(0,0))
{
    m_elements.push_back(&line_topRight);
    m_elements.push_back(&line_botRight);
    m_elements.push_back(&line_topLeft);
    m_elements.push_back(&line_botLeft);
    m_elements.push_back(&line_static);
    m_elements.push_back(&line_hidden);
    m_elements.push_back(&grid_none);
    m_elements.push_back(&grid_square);
    m_elements.push_back(&grid_hex);
    m_elements.push_back(&draw_button);
    m_elements.push_back(&clear_button);
    m_elements[m_currentLine-1]->SetActive(true);
}

Runner::~Runner() {

}

void Runner::HandleEvents() {
    sf::Event event;
    while(m_iter_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            m_iter_window.close();
    }
    while(m_window.pollEvent(event)) {
    switch(event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::MouseMoved:
            if(event.mouseButton.y > GUI_HEIGHT_OFFSET) {
                m_line.SetPosition(m_line.GetStart(), m_grid.SnapToNearest(sf::Vector2f(sf::Mouse::getPosition(m_window))));
            }
            break;
        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Button::Right) {
                m_drawingLine = false;
                break;
            }
            if(event.mouseButton.y < GUI_HEIGHT_OFFSET) { // Above grid
                for(int iii = 0; iii < m_elements.size(); iii++) {
                    if(m_elements[iii]->IsClicked(event.mouseButton.x, event.mouseButton.y)) {
                        m_elements[iii]->OnClick(event.mouseButton.x, event.mouseButton.y);
                        if(iii <= 5) { // Line type
                            m_elements[m_currentLine-1]->SetActive(false);
                            m_currentLine = (Line::line_type)(iii+1);
                            m_line.SetType(m_currentLine);
                            m_elements[m_currentLine-1]->SetActive(true);
                        }
                        else if(iii < 9){ // Grid
                            m_grid.SetType((Grid::grid_type)(iii-6));
                        } else if(iii == 9) { // Draw
                            m_iter.SetBase(m_base);
                        } else if(iii == 10) { // Clear
                            m_base = Fractal_Element();
                            m_drawingLine = false;
                        }
                    }
                }
            } else { // On the grid
                if(!m_drawingLine) {
                    m_drawingLine = true;
                } else {
                    m_base.AddLine(m_line);
                }
                m_line.SetPosition(m_grid.SnapToNearest(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)),
                                   m_grid.SnapToNearest(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)));
            }
            break;
        case sf::Event::KeyPressed:
            if(sf::Keyboard::Num1 <= event.key.code &&
               event.key.code <= sf::Keyboard::Num6) {
                m_elements[m_currentLine-1]->SetActive(false);
                m_currentLine = (Line::line_type)(event.key.code - sf::Keyboard::Num1+1);
                m_line.SetType(m_currentLine);
                m_elements[m_currentLine-1]->SetActive(true);
            }
            break;
        default:
            break;
        }
    }
}

void Runner::Draw() {
    m_window.clear(sf::Color::White);
    m_iter_window.clear(sf::Color::White);

    std::vector<GUI_Element*>::iterator it;
    for(it = m_elements.begin(); it != m_elements.end(); it++)
        (*it)->Draw();
    m_grid.Draw();

    if(m_drawingLine)
        m_line.Draw(m_window, false);

    m_base.Draw(m_window, false);
    m_iter.Draw();

    m_window.display();
    m_iter_window.display();
}


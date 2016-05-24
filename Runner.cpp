#include "Runner.h"

Runner::Runner(sf::RenderWindow& window, sf::RenderWindow& iter_window, sf::Font& font) :
    m_window(window),
    m_font(font),
    m_iter_window(iter_window, font),
    m_base(),
    m_currentLine(Line::lt_topRight),
    m_elements(0),
    m_grid(window, sf::Vector2f(0, GUI_HEIGHT_OFFSET), sf::Vector2f(m_window.getSize()), Grid::gt_square),
    m_startedTemplate(false),
    m_finishedTemplate(false),
    m_drawingLine(false),
    m_line(m_currentLine, sf::Vector2f(0,0), sf::Vector2f(0,0))
{
    //TODO: Make relative to window & each other
    // Line Selection Buttons
    m_elements.push_back(new Button(&window, &font, 5, 5, 100, 15, "TopRight(1)"));
    m_elements.push_back(new Button(&window, &font, 110, 5, 100, 15, "BotRight(2)"));
    m_elements.push_back(new Button(&window, &font, 215, 5, 100, 15, "TopLeft(3)"));
    m_elements.push_back(new Button(&window, &font, 320, 5, 100, 15, "BotLeft(4)"));
    m_elements.push_back(new Button(&window, &font, 425, 5, 100, 15, "Static(5)"));
    m_elements.push_back(new Button(&window, &font, 530, 5, 100, 15, "Hidden(6)"));
    // Grid Selection Buttons
    m_elements.push_back(new Button(&window, &font, 635, 5, 100, 15, "No Grid"));
    m_elements.push_back(new Button(&window, &font, 740, 5, 100, 15, "Square Grid"));
    m_elements.push_back(new Button(&window, &font, 845, 5, 100, 15, "Hex Grid"));
    // Action Buttons
    m_elements.push_back(new Button(&window, &font, 950, 5, 100, 15, "Draw"));
    m_elements.push_back(new Button(&window, &font, 1055, 5, 100, 15, "Clear"));
    m_elements[m_currentLine-1]->SetActive(true);
}

Runner::~Runner() {
    for(auto it = m_elements.begin(); it != m_elements.end(); it++) {
        delete (*it);
    }
}

void Runner::HandleEvents() {
    m_iter_window.HandleEvents();
    sf::Event event;
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
                if(m_startedTemplate) {
                    m_finishedTemplate = true;
                    m_base.DrawBaseline();
                }
                break;
            }
            if(event.mouseButton.y < GUI_HEIGHT_OFFSET) { // Above grid
                for(size_t iii = 0; iii < m_elements.size(); iii++) {
                    if(m_elements[iii]->IsClicked(event.mouseButton.x, event.mouseButton.y)) {
                        m_elements[iii]->OnClick(event.mouseButton.x, event.mouseButton.y);
                        if(iii <= 5) { // Line type
                            UpdateLineType(iii+1);
                            }
                        else if(iii < 9){ // Grid
                            m_grid.SetType((Grid::grid_type)(iii-6));
                        } else if(iii == 9) { // Draw
                            m_iter_window.StartNewIteration(m_base.ToElement());
                        } else if(iii == 10) { // Clear
                            m_base.Clear();
                            m_startedTemplate = false;
                            m_finishedTemplate = false;
                            m_drawingLine = false;
                        }
                    }
                }
            } else { // On the grid
                if(!m_startedTemplate) { // Haven't started drawing the template yet
                    m_startedTemplate = true;
                    m_drawingLine = true;
                    m_base.StartAtPoint(m_grid.SnapToNearest(sf::Vector2f(sf::Mouse::getPosition(m_window))));
                }
                else if(!m_finishedTemplate) { // Currently drawing the template
                    m_base.AddLine(m_grid.SnapToNearest(sf::Vector2f(sf::Mouse::getPosition(m_window))), m_currentLine);
                } else { // Done drawing the template
                    m_base.SelectNear(sf::Vector2f(sf::Mouse::getPosition(m_window)));
                    // TODO: Allow movement of the template
                }
                m_line.SetPosition(m_grid.SnapToNearest(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)),
                                   m_grid.SnapToNearest(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)));
            }
            break;
        case sf::Event::KeyPressed:
            if(sf::Keyboard::Num1 <= event.key.code &&
               event.key.code <= sf::Keyboard::Num6) {
                 UpdateLineType(event.key.code - sf::Keyboard::Num1+1);
               }
            break;
        default:
            break;
        }
    }
}

void Runner::Draw() {
    m_window.clear(sf::Color::White);

    std::vector<GUI_Element*>::iterator it;
    for(it = m_elements.begin(); it != m_elements.end(); it++)
        (*it)->Draw();
    m_grid.Draw();

    if(m_drawingLine)
        m_line.Draw(m_window, false);

    m_base.Draw(m_window, false);

    m_window.display();

    m_iter_window.Draw();
}

void Runner::UpdateLineType(int newTypeButton) {
    m_elements[m_currentLine-1]->SetActive(false);
    m_currentLine = (Line::line_type)(newTypeButton);
    m_line.SetType(m_currentLine);
    m_elements[m_currentLine-1]->SetActive(true);
    m_base.ChangeType(m_currentLine);
}


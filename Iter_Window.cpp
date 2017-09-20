#include "Iter_Window.h"
#include "gui/Button.h"
#include "gui/text.h"
#include "gui/checkbox.h"
#include "utils.h"
#include "constants.h"

#include <algorithm>

#ifdef _WIN32
#include <Windows.h>
#endif

Iter_Window::Iter_Window(sf::RenderWindow& window, sf::Font& font) :
    m_window(window),
    m_font(font),
    m_iterator(),
    m_input(&window, &font, 110, 30, 300, 15, "File:"),
    m_success(&window, &font, 460, 30, 1000, 15, ""),
    m_drawPrevious(&window, &font, 1000, 30, "Consective levels", false),
    m_elements(0),
    m_currentLevel(0)
{
    if(!m_window.isOpen()) {
        m_window.create(sf::VideoMode(1200, 724), "FractaSketch", sf::Style::Titlebar | sf::Style::Close);
        m_window.setPosition(sf::Vector2i(0, 0));
        m_input = InputBox(&window, &font, 110, 30, 300, 15, "File:");
        m_success = InputBox(&window, &font, 460, 30, 1000, 15, "");
        m_drawPrevious = Checkbox(&window, &font, 1000, 30, "Consective levels", false);
    }
    //TODO: Make relative to window & each other
    m_elements.push_back(new Button(&window, &font, 5, 5, 100, 15, "Level 0"));
    m_elements.push_back(new Button(&window, &font, 110, 5, 100, 15, "Level 1"));
    m_elements.push_back(new Button(&window, &font, 215, 5, 100, 15, "Level 2"));
    m_elements.push_back(new Button(&window, &font, 320, 5, 100, 15, "Level 3"));
    m_elements.push_back(new Button(&window, &font, 425, 5, 100, 15, "Level 4"));
    m_elements.push_back(new Button(&window, &font, 530, 5, 100, 15, "Level 5"));
    m_elements.push_back(new Button(&window, &font, 635, 5, 100, 15, "Level 6"));
    m_elements.push_back(new Button(&window, &font, 740, 5, 100, 15, "Level 7"));
    m_elements.push_back(new Button(&window, &font, 845, 5, 100, 15, "Level 8"));
    m_elements.push_back(new Button(&window, &font, 950, 5, 100, 15, "Level 9"));
    m_elements.push_back(new Button(&window, &font, 1055, 5, 100, 15, "Infinity"));
    m_elements.push_back(new Button(&window, &font, 5, 30, 100, 15, "Save"));
    m_success.SetOutlineColor(sf::Color::White);
    m_window.close();
}

Iter_Window::~Iter_Window() {
    m_window.close();
    for(auto it = m_elements.begin(); it != m_elements.end(); it++) {
        delete (*it);
    }
    m_elements.clear();
}
#include <iostream> //DEBUGGING, REMOVE
void Iter_Window::HandleEvents() {
    if(!m_window.isOpen())
        return;
    sf::Event event;
    while(m_window.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::MouseButtonPressed:
            m_input.SetActive(false); // Deactivate m_input if we click anywhere else
            m_success.SetText("");
            if(event.mouseButton.button == sf::Mouse::Button::Left) {
                for(size_t iii = 0; iii <= ITERATOR_LEVELS + 1; iii++) {
                    if(m_elements[iii]->IsClicked(event.mouseButton.x, event.mouseButton.y)) {
                        m_elements[iii]->OnClick(event.mouseButton.x, event.mouseButton.y);
                        m_elements[m_currentLevel]->SetActive(false);
                        m_currentLevel = iii;
                        m_elements[m_currentLevel]->SetActive(true);
                        m_iterator.SetLevel(m_currentLevel);
                    }
                }
                // Save button
                if(m_elements[ITERATOR_LEVELS + 2]->IsClicked(event.mouseButton.x, event.mouseButton.y)) {
                    sf::RenderTexture tex;
                    tex.create(m_window.getSize().x, m_window.getSize().y);
                    tex.clear(sf::Color::White);
                    m_iterator.Draw(tex, m_drawPrevious.IsToggled());
                    tex.display();

                    sf::Image img = tex.getTexture().copyToImage();
                    std::string filename = m_input.GetText();
#ifdef _WIN32
                    if (filename.size() == 0) {
                        TCHAR fn[256];
                        fn[0] = '\0';
                        OPENFILENAME ofn = { 0 };
                        ofn.lStructSize = sizeof(ofn);
                        ofn.hwndOwner = m_window.getSystemHandle();
                        ofn.lpstrFile = fn;
                        ofn.nMaxFile = sizeof(fn) / sizeof(fn[0]);
                        ofn.lpstrFilter = "PNG image (.png)\0*.png\0All Files\0*.*\0";
                        ofn.nFilterIndex = 0;
                        ofn.lpstrFileTitle = NULL;
                        ofn.nMaxFileTitle = 0;
                        ofn.lpstrInitialDir = NULL;
                        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

                        GetSaveFileName(&ofn);

                        filename = fn;
                    }
                    else {
#endif
                        filename = GetProperPath(filename);
                        if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".png")
                            filename += ".png";
#ifdef _WIN32
                    }
#endif

                    if (img.saveToFile(filename))
                        m_success.SetText("Image saved!");
                    else
                        m_success.SetText("Save failed :(");
                }
                if(m_input.IsClicked(event.mouseButton.x, event.mouseButton.y)) {
                    m_input.OnClick(event.mouseButton.x, event.mouseButton.y);
                    m_input.SetActive(true);
                }
                if(m_drawPrevious.IsClicked(event.mouseButton.x, event.mouseButton.y)) {
                    m_drawPrevious.OnClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
            break;
        case sf::Event::KeyPressed:
            if(sf::Keyboard::Num0 < event.key.code &&
               event.key.code <= sf::Keyboard::Num9 &&
               !m_input.GetActive()) {
                UpdateLevel(event.key.code - sf::Keyboard::Num0);
            } else if(event.key.code == sf::Keyboard::Tilde) { // Level 0
                UpdateLevel(0);
            } else if(event.key.code == sf::Keyboard::Num0) { // Level Infinity
                UpdateLevel(ITERATOR_LEVELS+1);
            } else if(event.key.code == sf::Keyboard::Left) {
                UpdateLevel(std::max((int)m_currentLevel - 1, 0));
            } else if (event.key.code == sf::Keyboard::Right) {
                UpdateLevel(std::min((int)m_currentLevel + 1, ITERATOR_LEVELS + 1));
            }
            else {
                m_input.OnKeyPressed(event.key.code);
            }
            break;
        case sf::Event::TextEntered:
            if(m_input.GetActive())
                m_input.OnTextEntered(event.text.unicode);
            break;
        default:
            break;
        }
    }
}

void Iter_Window::Draw() {
    if(!m_window.isOpen())
        return;
    m_window.clear(sf::Color::White);

    m_success.Draw();
    m_iterator.Draw(m_window, m_drawPrevious.IsToggled());

    for(auto it = m_elements.begin(); it != m_elements.end(); it++) {
        (*it)->Draw();
    }
    m_input.Draw();
    m_drawPrevious.Draw();

    m_window.display();
}

void Iter_Window::StartNewIteration(Fractal_Template base) {
    if(!m_window.isOpen()) {
        m_window.create(sf::VideoMode(1200, 724), "FractaSketch", sf::Style::Titlebar | sf::Style::Close);
        m_window.setPosition(sf::Vector2i(0, 0));
    }
    m_window.requestFocus();
    m_success.SetText("");
    m_elements[m_currentLevel]->SetActive(false);
    m_currentLevel = 0;
    m_elements[m_currentLevel]->SetActive(true);

    m_iterator.SetBase(base);
}

void Iter_Window::UpdateLevel(size_t newLevel) {
    m_elements[m_currentLevel]->SetActive(false);
    m_currentLevel = newLevel;
    m_elements[m_currentLevel]->SetActive(true);
    m_iterator.SetLevel(m_currentLevel);
}

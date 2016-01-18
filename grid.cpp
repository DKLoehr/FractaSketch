#include "Grid.h"
#include <queue>

Grid::Grid(sf::RenderWindow* window, sf::Vector2f topLeft, sf::Vector2f botRight, grid_type type):
    m_window(window),
    m_position(topLeft),
    m_size(botRight-topLeft),
    m_type(type)
{
    FillGrids();
}

Grid::~Grid()
{
    //dtor
}

void Grid::Draw() {
    m_window->draw(m_grids[m_type]);
}

void Grid::FillGrids() {
    m_grids[gt_none] = sf::VertexArray(sf::Points, 0);

    // Initialize the square grid
    double rows = m_size.y / SQUARE_SCALE,
           cols = m_size.x / SQUARE_SCALE;
    for(int iii = 0; iii < rows; iii++) {
        for(int jjj = 0; jjj < cols; jjj++) {
            m_grids[gt_square].append(sf::Vertex(m_position + sf::Vector2f(jjj*SQUARE_SCALE, iii*SQUARE_SCALE), sf::Color::Black));
        }
    }

    //Initialize the hex grid
    double dx = 3*HEX_SCALE,
           dy = sqrt(3)/2*HEX_SCALE;
    rows = m_size.y / dy;
    cols = m_size.x / dx;
    for(int iii = 0; iii < rows; iii++) {
        for(int jjj = 0; jjj < cols; jjj++) {
            for(int kkk = 0; kkk < 6; kkk++) {
                sf::Vector2f center = m_position + sf::Vector2f(jjj*dx, iii*dy) + sf::Vector2f(1.5*HEX_SCALE*(iii % 2 + 1), 0);
                m_grids[gt_hex].append(sf::Vertex(center + sf::Vector2f(cos(M_PI/3*kkk), sin(M_PI/3*kkk)) * (float)HEX_SCALE,
                                                   sf::Color::Black));
            }
        }
    }
}
// Returns the point on the grid nearest to the input point.
// If there is no grid, returns the input
sf::Vector2f Grid::SnapToNearest(sf::Vector2f point) {
    if(m_type == gt_none)
        return point;
    else if(m_type == gt_square) { // Can just round to nearest int
        return point;
    } else { // Hex grid
        return point;
    }
}

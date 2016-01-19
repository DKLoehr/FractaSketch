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

    // Initialize the hex grid by tracking the centers of each hex and
    // drawing the 6 points around each
    // TODO: Remove duplicates
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
// TODO: The implementation for hex grids is ridiculously inefficient.
// I haven't noticed a performance hit yet, but it should be dealt with
sf::Vector2f Grid::SnapToNearest(sf::Vector2f point) {
    if(m_type == gt_none)
        return point;
    else if(m_type == gt_square) { // Round each coordinate to nearest multiple of SQUARE_SCALE
        if(point.x < m_position.x) point.x = m_position.x;
        if(point.x > (m_position+m_size).x) point.x = (m_position+m_size).x;
        if(point.y < m_position.y) point.y = m_position.y;
        if(point.y > (m_position+m_size).y) point.y = (m_position+m_size).y;
        point.x = ((int)((point.x - m_position.x)/SQUARE_SCALE + .5))*SQUARE_SCALE + m_position.x;
        point.y = ((int)((point.y - m_position.y)/SQUARE_SCALE + .5))*SQUARE_SCALE + m_position.y;
        return point;
    } else { // Hex grid
        unsigned int minDist = -1;
        sf::Vector2f minDistPoint = point;
        for(int iii = 0; iii < m_grids[2].getVertexCount(); iii++) {
            sf::Vector2f dist = m_grids[2][iii].position - point;
            int length = sqrt(dist.x*dist.x + dist.y*dist.y);
            if(length < minDist) {
                minDist = length;
                minDistPoint = m_grids[2][iii].position;
            }
        }
        return minDistPoint;
    }
}

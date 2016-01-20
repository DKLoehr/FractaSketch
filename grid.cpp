#include "Grid.h"
#include <queue>

Grid::Grid(sf::RenderWindow* window, sf::Vector2f topLeft, sf::Vector2f botRight, grid_type type = gt_none):
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
    std::vector<sf::CircleShape>::iterator it;
    for(it = m_grids[m_type].begin(); it != m_grids[m_type].end(); it++)
        m_window->draw(*it);
}

void Grid::FillGrids() {
    m_grids[gt_none] = std::vector<sf::CircleShape>(0);

    sf::CircleShape point(GRID_DOT_RAD);
    point.setFillColor(sf::Color::Black);
    point.setOrigin(GRID_DOT_RAD, GRID_DOT_RAD); // Position relative to center instead of top-left corner
    // Initialize the square grid
    double rows = m_size.y / GRID_SQUARE_SCALE,
           cols = m_size.x / GRID_SQUARE_SCALE;
    for(int iii = 0; iii < rows; iii++) {
        for(int jjj = 0; jjj < cols; jjj++) {
            point.setPosition(m_position + sf::Vector2f(jjj*GRID_SQUARE_SCALE, iii*GRID_SQUARE_SCALE));
            m_grids[gt_square].push_back(point);
        }
    }

    // Initialize the hex grid by tracking the centers of each hex and
    // drawing the 6 points around each
    // TODO: Remove duplicates
    double dx = 3*GRID_HEX_SCALE,
           dy = sqrt(3)/2*GRID_HEX_SCALE;
    rows = m_size.y / dy;
    cols = m_size.x / dx;
    for(int iii = 0; iii < rows; iii++) {
        for(int jjj = 0; jjj < cols; jjj++) {
            sf::Vector2f center = m_position
                                 + sf::Vector2f(jjj*dx, iii*dy)
                                 + sf::Vector2f(1.5*GRID_HEX_SCALE*(iii % 2 + 1), 0); // Shift left or not based on row num
            for(int kkk = 0; kkk < 6; kkk++) {
                point.setPosition(center + (sf::Vector2f(cos(M_PI/3*kkk), sin(M_PI/3*kkk)) * (float)GRID_HEX_SCALE));
                m_grids[gt_hex].push_back(point);
            }
        }
    }
}

void Grid::SetType(grid_type newType) {
    m_type = newType;
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
        point.x = ((int)((point.x - m_position.x)/GRID_SQUARE_SCALE + .5))*GRID_SQUARE_SCALE + m_position.x;
        point.y = ((int)((point.y - m_position.y)/GRID_SQUARE_SCALE + .5))*GRID_SQUARE_SCALE + m_position.y;
        return point;
    } else { // Hex grid
        unsigned int minDist = -1;
        sf::Vector2f minDistPoint = point;
        std::vector<sf::CircleShape>::iterator it;
        for(it = m_grids[gt_hex].begin(); it != m_grids[gt_hex].end(); it++) {
            sf::Vector2f dist = it->getPosition()  - point;
            int length = sqrt(dist.x*dist.x + dist.y*dist.y);
            if(length < minDist) {
                minDist = length;
                minDistPoint = it->getPosition();
            }
        }
        return minDistPoint;
    }
}

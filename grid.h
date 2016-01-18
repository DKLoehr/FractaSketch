#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include "constants.h"

enum grid_type {
    gt_none = 0,  // Invisible
    gt_square = 1,
    gt_hex = 2
};

class Grid
{
private:
    sf::RenderWindow* m_window;
    sf::Vector2f m_position;
    sf::Vector2f m_size;

    grid_type m_type;

    sf::VertexArray m_grids[GRID_TYPE_NUM];

public:
    Grid(sf::RenderWindow* window, sf::Vector2f topLeft, sf::Vector2f botRight, grid_type type);
    ~Grid();

    void Draw();
    void FillGrids();
    // Returns the point on the grid nearest to the input point
    sf::Vector2f SnapToNearest(sf::Vector2f point);
};

#endif // GRID_H

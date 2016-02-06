#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <cmath>
#ifndef M_PI
    #define M_PI 3.1415926535897932385
#endif // M_PI

// Grid settings
#define GRID_TYPE_NUM 3
#define GRID_SQUARE_SCALE 30.0 // Distance between points
#define GRID_HEX_SCALE    25.0
#define GRID_DOT_RAD 1.0

// Line settings
#define LINE_ARROW_HEIGHT 7.5
#define LINE_ARROW_LENGTH 15.0
#define LINE_DOT_SIZE 5.0 // Length of lines in dotted lines
#define LINE_DOT_DIST 1.0 // Distance between dots in hidden lines

// GUI settings
#define GUI_HEIGHT_OFFSET 100

// Iterator settings
#define ITERATOR_LEVELS 11

#endif // CONSTANTS_H

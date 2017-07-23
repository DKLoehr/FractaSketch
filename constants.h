#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <cmath>
#ifndef M_PI
    #define M_PI 3.1415926535897932385
#endif // M_PI

// Grid settings
#define GRID_TYPE_NUM 3
#define GRID_DOT_RAD 2.0

// Line settings
#define LINE_ARROW_HEIGHT 7.5
#define LINE_ARROW_LENGTH 15.0
#define LINE_DOT_SIZE 5.0 // Length of lines in dotted lines
#define LINE_DOT_DIST 1.0 // Distance between dots in hidden lines

// Fractal Template Settings
#define TEMPLATE_DOT_RAD GRID_DOT_RAD
#define TEMPLATE_SELECT_DOT_RAD 8.0 // How close you have to be to a dot to select it
#define TEMPLATE_SELECT_LINE_RAD 4.0 // How close you have to be to a line to select it

// GUI settings
#define GUI_HEIGHT_OFFSET 100

// Iterator settings
#define ITERATOR_LEVELS 9

// Configuration settings
#define CONFIG_FILE "FractaSketch_config.cfg"

#endif // CONSTANTS_H

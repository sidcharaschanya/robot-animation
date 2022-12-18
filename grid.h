#ifndef C_COURSEWORK_GRID_H
#define C_COURSEWORK_GRID_H

#include "graphics.h"

typedef enum GridContent {
    empty, marker, obstacle
} GridContent;

typedef struct Grid {
    int size;
    int windowSideLength;
    int cellSideLength;
    colour backgroundColor;
    colour lineColor;
    colour markerColor;
    colour obstacleColor;
    GridContent **contents;
} Grid;

void initGridContents(Grid *);

void drawGridBackground(Grid *);

void drawGridLines(Grid *);

void drawMarker(Grid *);

void drawObstacles(Grid *);

void drawBackground(Grid *);

#endif

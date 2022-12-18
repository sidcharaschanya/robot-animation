#include <stdlib.h>
#include "grid.h"

void initGridContents(Grid *grid) {
    grid->contents = malloc(sizeof(GridContent *) * grid->size);

    for (int row = 0; row < grid->size; row++) {
        grid->contents[row] = malloc(sizeof(GridContent) * grid->size);

        for (int col = 0; col < grid->size; col++) {
            grid->contents[row][col] = empty;
        }
    }
}

void drawGridBackground(Grid *grid) {
    setColour(grid->backgroundColor);
    fillRect(0, 0, grid->windowSideLength, grid->windowSideLength);
}

void drawGridLines(Grid *grid) {
    setColour(grid->lineColor);

    for (int i = 0; i < grid->size; i++) {
        drawLine(0, i * grid->cellSideLength, grid->windowSideLength, i * grid->cellSideLength);
        drawLine(i * grid->cellSideLength, 0, i * grid->cellSideLength, grid->windowSideLength);
    }
}

void drawMarker(Grid *grid) {
    setColour(grid->markerColor);

    for (int row = 0; row < grid->size; row++) {
        for (int col = 0; col < grid->size; col++) {
            if (grid->contents[row][col] == marker) {
                fillRect(
                        col * grid->cellSideLength,
                        row * grid->cellSideLength,
                        grid->cellSideLength,
                        grid->cellSideLength
                );
            }
        }
    }
}

void drawObstacles(Grid *grid) {
    setColour(grid->obstacleColor);

    for (int row = 0; row < grid->size; row++) {
        for (int col = 0; col < grid->size; col++) {
            if (grid->contents[row][col] == obstacle) {
                fillRect(
                        col * grid->cellSideLength,
                        row * grid->cellSideLength,
                        grid->cellSideLength,
                        grid->cellSideLength
                );
            }
        }
    }
}

void drawBackground(Grid *grid) {
    background();
    drawGridBackground(grid);
    drawGridLines(grid);
    drawMarker(grid);
    drawObstacles(grid);
}

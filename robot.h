#ifndef C_COURSEWORK_ROBOT_H
#define C_COURSEWORK_ROBOT_H

#include "grid.h"

typedef enum Orientation {
    east = 0, west = 1, north = 2, south = 3
} Orientation;

typedef enum TurnDirection {
    right = 0, left = 1, randomized = 2
} TurnDirection;

typedef struct Robot {
    int xCoord;
    int yCoord;
    Orientation orientation;
    TurnDirection turnDirection;
    colour color;
    int sleepTime;
} Robot;

void forward(Robot *);

void turnLeft(Robot *);

void turnRight(Robot *);

void turn(Robot *);

int atMarker(Robot *, Grid *);

int facingAdjacentEdge(Robot *, Grid *);

int facingAdjacentObstacle(Robot *, Grid *);

int canMoveForward(Robot *, Grid *);

void drawRobotFacingEast(Robot *, Grid *);

void drawRobotFacingWest(Robot *, Grid *);

void drawRobotFacingNorth(Robot *, Grid *);

void drawRobotFacingSouth(Robot *, Grid *);

void drawRobot(Robot *, Grid *);

void animateRobot(Robot *, Grid *);

#endif

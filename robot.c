#include <stdlib.h>
#include <time.h>
#include "robot.h"

void forward(Robot *robot) {
    switch (robot->orientation) {
        case east:
            robot->xCoord += 1;
            break;
        case west:
            robot->xCoord -= 1;
            break;
        case north:
            robot->yCoord -= 1;
            break;
        case south:
            robot->yCoord += 1;
            break;
    }
}

void turnLeft(Robot *robot) {
    switch (robot->orientation) {
        case east:
            robot->orientation = north;
            break;
        case north:
            robot->orientation = west;
            break;
        case west:
            robot->orientation = south;
            break;
        case south:
            robot->orientation = east;
            break;
    }
}

void turnRight(Robot *robot) {
    switch (robot->orientation) {
        case east:
            robot->orientation = south;
            break;
        case south:
            robot->orientation = west;
            break;
        case west:
            robot->orientation = north;
            break;
        case north:
            robot->orientation = east;
            break;
    }
}

void turn(Robot *robot) {
    switch (robot->turnDirection) {
        case right:
            turnRight(robot);
            break;
        case left:
            turnLeft(robot);
            break;
        case randomized:
            // Turn randomly by checking if a random number is even or odd
            if (rand() % 2 == 0) {
                turnRight(robot);
            } else {
                turnLeft(robot);
            }
            break;
    }
}

int atMarker(Robot *robot, Grid *grid) {
    if (grid->contents[robot->yCoord][robot->xCoord] == marker) {
        return 1;
    }
    return 0;
}

int facingAdjacentEdge(Robot *robot, Grid *grid) {
    if (robot->xCoord == 0 && robot->orientation == west) {
        return 1; // Robot is at west edge and facing it
    }
    if (robot->xCoord == grid->size - 1 && robot->orientation == east) {
        return 1; // Robot is at east edge and facing it
    }
    if (robot->yCoord == 0 && robot->orientation == north) {
        return 1; // Robot is at north edge and facing it
    }
    if (robot->yCoord == grid->size - 1 && robot->orientation == south) {
        return 1; // Robot is at south edge and facing it
    }
    return 0;
}

int facingAdjacentObstacle(Robot *robot, Grid *grid) {
    int nextXCoord = robot->xCoord;
    int nextYCoord = robot->yCoord;

    switch (robot->orientation) {
        case east:
            nextXCoord += 1;
            break;
        case west:
            nextXCoord -= 1;
            break;
        case north:
            nextYCoord -= 1;
            break;
        case south:
            nextYCoord += 1;
            break;
    }

    if (grid->contents[nextYCoord][nextXCoord] == obstacle) {
        return 1;
    }
    return 0;
}

int canMoveForward(Robot *robot, Grid *grid) {
    if (facingAdjacentEdge(robot, grid) || facingAdjacentObstacle(robot, grid)) {
        return 0;
    }
    return 1;
}

void drawRobotFacingEast(Robot *robot, Grid *grid) {
    int robotFacingEastXCoords[] = {
            robot->xCoord * grid->cellSideLength,
            (robot->xCoord + 1) * grid->cellSideLength,
            robot->xCoord * grid->cellSideLength
    };

    int robotFacingEastYCoords[] = {
            robot->yCoord * grid->cellSideLength,
            (int) ((robot->yCoord + 0.5) * grid->cellSideLength),
            (robot->yCoord + 1) * grid->cellSideLength
    };

    fillPolygon(3, robotFacingEastXCoords, robotFacingEastYCoords);
}

void drawRobotFacingWest(Robot *robot, Grid *grid) {
    int robotFacingWestXCoords[] = {
            (robot->xCoord + 1) * grid->cellSideLength,
            robot->xCoord * grid->cellSideLength,
            (robot->xCoord + 1) * grid->cellSideLength
    };

    int robotFacingWestYCoords[] = {
            (robot->yCoord + 1) * grid->cellSideLength,
            (int) ((robot->yCoord + 0.5) * grid->cellSideLength),
            robot->yCoord * grid->cellSideLength
    };

    fillPolygon(3, robotFacingWestXCoords, robotFacingWestYCoords);
}

void drawRobotFacingNorth(Robot *robot, Grid *grid) {
    int robotFacingNorthXCoords[] = {
            robot->xCoord * grid->cellSideLength,
            (int) ((robot->xCoord + 0.5) * grid->cellSideLength),
            (robot->xCoord + 1) * grid->cellSideLength
    };

    int robotFacingNorthYCoords[] = {
            (robot->yCoord + 1) * grid->cellSideLength,
            robot->yCoord * grid->cellSideLength,
            (robot->yCoord + 1) * grid->cellSideLength
    };

    fillPolygon(3, robotFacingNorthXCoords, robotFacingNorthYCoords);
}

void drawRobotFacingSouth(Robot *robot, Grid *grid) {
    int robotFacingSouthXCoords[] = {
            (robot->xCoord + 1) * grid->cellSideLength,
            (int) ((robot->xCoord + 0.5) * grid->cellSideLength),
            robot->xCoord * grid->cellSideLength
    };

    int robotFacingSouthYCoords[] = {
            robot->yCoord * grid->cellSideLength,
            (robot->yCoord + 1) * grid->cellSideLength,
            robot->yCoord * grid->cellSideLength
    };

    fillPolygon(3, robotFacingSouthXCoords, robotFacingSouthYCoords);
}

void drawRobot(Robot *robot, Grid *grid) {
    // Robot from previous iteration of animation should not be visible
    clear();

    switch (robot->orientation) {
        case east:
            drawRobotFacingEast(robot, grid);
            break;
        case west:
            drawRobotFacingWest(robot, grid);
            break;
        case north:
            drawRobotFacingNorth(robot, grid);
            break;
        case south:
            drawRobotFacingSouth(robot, grid);
            break;
    }
}

void animateRobot(Robot *robot, Grid *grid) {
    foreground();
    setColour(robot->color);

    // Reference for generating random numbers is https://www.javatpoint.com/random-function-in-c
    if (robot->turnDirection == randomized) {
        // Seed random number generator using current time to ensure seed is always unique
        srand(time(NULL));
    }

    while (!atMarker(robot, grid)) {
        drawRobot(robot, grid);

        if (canMoveForward(robot, grid)) {
            forward(robot);
        } else {
            turn(robot);
        }

        // Briefly pause execution to control robot movement speed
        sleep(robot->sleepTime);
    }

    // If while loop terminates because marker is reached, draw robot at marker
    drawRobot(robot, grid);
}

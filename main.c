#include <stdio.h>
#include <string.h>
#include "robot.h"

// Default values for grid and robot if data file not given
static Grid grid = {10, 400, 40, white, black, lightgray, red};
static Robot robot = {0, 0, east, right, green, 200};

// Possible data file attributes are Grid, Robot, MarkerColor, Marker, ObstacleColor, and Obstacle
static const int maxDataFileAttributeLength = 14;

// These constants are used for reading data file strings and converting them to enum values
static const char *colorStrings[] = {
        "black", "blue", "cyan", "darkgray", "gray", "green", "lightgray", "magenta", "orange", "pink", "red", "white",
        "yellow"
};
static const int maxColorStringLength = 10;
static const char *orientationStrings[] = {"east", "west", "north", "south"};
static const int maxOrientationStringLength = 6;
static const char *turnDirectionStrings[] = {"right", "left", "randomized"};
static const int maxTurnDirectionStringLength = 11;

void assignStringToColor(char *string, colour *colorPtr) {
    for (int i = 0; i < sizeof(colorStrings) / sizeof(char *); i++) {
        if (strcmp(colorStrings[i], string) == 0) {
            *colorPtr = (colour) i;
            break;
        }
    }
}

void assignStringToOrientation(char *string, Orientation *orientationPtr) {
    for (int i = 0; i < sizeof(orientationStrings) / sizeof(char *); i++) {
        if (strcmp(orientationStrings[i], string) == 0) {
            *orientationPtr = (Orientation) i;
            break;
        }
    }
}

void assignStringToTurnDirection(char *string, TurnDirection *turnDirectionPtr) {
    for (int i = 0; i < sizeof(turnDirectionStrings) / sizeof(char *); i++) {
        if (strcmp(turnDirectionStrings[i], string) == 0) {
            *turnDirectionPtr = (TurnDirection) i;
            break;
        }
    }
}

void readGridData(FILE *dataFilePtr) {
    char gridBackgroundColorString[maxColorStringLength];
    char gridLineColorString[maxColorStringLength];

    fscanf(
            dataFilePtr,
            "%d %d %s %s",
            &grid.size,
            &grid.windowSideLength,
            gridBackgroundColorString,
            gridLineColorString
    );

    grid.cellSideLength = grid.windowSideLength / grid.size;

    assignStringToColor(gridBackgroundColorString, &grid.backgroundColor);
    assignStringToColor(gridLineColorString, &grid.lineColor);

    initGridContents(&grid);
}

void readRobotData(FILE *dataFilePtr) {
    char robotOrientationString[maxOrientationStringLength];
    char robotTurnDirectionString[maxTurnDirectionStringLength];
    char robotColorString[maxColorStringLength];

    fscanf(
            dataFilePtr,
            "%d %d %s %s %s %d",
            &robot.xCoord,
            &robot.yCoord,
            robotOrientationString,
            robotTurnDirectionString,
            robotColorString,
            &robot.sleepTime
    );

    assignStringToOrientation(robotOrientationString, &robot.orientation);
    assignStringToTurnDirection(robotTurnDirectionString, &robot.turnDirection);
    assignStringToColor(robotColorString, &robot.color);
}

void readMarkerColor(FILE *dataFilePtr) {
    char markerColorString[maxColorStringLength];

    fscanf(dataFilePtr, "%s", markerColorString);

    assignStringToColor(markerColorString, &grid.markerColor);
}

void readMarkerCoords(FILE *dataFilePtr) {
    int markerXCoord, markerYCoord;

    fscanf(dataFilePtr, "%d %d", &markerXCoord, &markerYCoord);

    grid.contents[markerYCoord][markerXCoord] = marker;
}

void readObstacleColor(FILE *dataFilePtr) {
    char obstacleColorString[maxColorStringLength];

    fscanf(dataFilePtr, "%s", obstacleColorString);

    assignStringToColor(obstacleColorString, &grid.obstacleColor);
}

void readObstacleCoords(FILE *dataFilePtr) {
    int obstacleXCoord, obstacleYCoord;

    fscanf(dataFilePtr, "%d %d", &obstacleXCoord, &obstacleYCoord);

    grid.contents[obstacleYCoord][obstacleXCoord] = obstacle;
}

void emptyFileLineBuffer(FILE *dataFilePtr) {
    char c;
    while ((c = (char) getc(dataFilePtr)) != '\n' && c != EOF);
}

void readDataFile(char *dataFileName) {
    // Reference for reading text files is https://www.guru99.com/c-file-input-output.html
    FILE *dataFilePtr = fopen(dataFileName, "r");
    char dataFileAttribute[maxDataFileAttributeLength];

    while (!feof(dataFilePtr)) {
        // Read first string in current line of data file
        fscanf(dataFilePtr, "%s", dataFileAttribute);

        // Proceed to read remaining data in current line of data file
        if (strcmp("Grid", dataFileAttribute) == 0) {
            readGridData(dataFilePtr);
        } else if (strcmp("Robot", dataFileAttribute) == 0) {
            readRobotData(dataFilePtr);
        } else if (strcmp("MarkerColor", dataFileAttribute) == 0) {
            readMarkerColor(dataFilePtr);
        } else if (strcmp("Marker", dataFileAttribute) == 0) {
            readMarkerCoords(dataFilePtr);
        } else if (strcmp("ObstacleColor", dataFileAttribute) == 0) {
            readObstacleColor(dataFilePtr);
        } else if (strcmp("Obstacle", dataFileAttribute) == 0) {
            readObstacleCoords(dataFilePtr);
        }

        // Move on to next line of data file
        emptyFileLineBuffer(dataFilePtr);
        dataFileAttribute[0] = '\0';
    }

    fclose(dataFilePtr);
}

int main(int argc, char **argv) {
    if (argc == 2) {
        readDataFile(argv[1]);
    } else {
        initGridContents(&grid);
    }

    setWindowSize(grid.windowSideLength, grid.windowSideLength);
    drawBackground(&grid);
    animateRobot(&robot, &grid);

    return 0;
}

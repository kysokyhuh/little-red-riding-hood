#ifndef GRID_H
#define GRID_H

#define MAX_SIZE 15

void initGrid(char grid[][MAX_SIZE], int size);
void displayGrid(char grid[][MAX_SIZE],
                 int size,
                 int LRRHX, int LRRHY,
                 char direction);
void printLegend(void);

/**
 * Place a single object on the grid at zero‐based (row,col).
 */
void placeElement(char grid[][MAX_SIZE],
                  int row, int col,
                  char symbol);

#endif // GRID_H

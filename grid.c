#include <stdio.h>
#include "headers/grid.h"

// ANSI clear‐screen
static void clearScreen(void) {
    printf("\x1b[2J\x1b[H");
}

void initGrid(char grid[][MAX_SIZE], int size) {
    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            grid[r][c] = '_';
}

void displayGrid(char grid[][MAX_SIZE],
                 int size,
                 int LRRHX, int LRRHY,
                 char direction)
{
    clearScreen();

    // top border
    printf("   ");
    for (int c = 0; c < size; c++) printf("+---");
    printf("+\n");

    for (int r = 0; r < size; r++) {
        printf("%2d ", r+1);
        for (int c = 0; c < size; c++) {
            char ch = grid[r][c];
            if (r==LRRHX && c==LRRHY) {
                switch (direction) {
                  case 'U': ch='^'; break;
                  case 'D': ch='v'; break;
                  case 'L': ch='<'; break;
                  case 'R': ch='>'; break;
                }
            }
            printf("| %c ", ch);
        }
        printf("|\n   ");
        for (int c = 0; c < size; c++) printf("+---");
        printf("+\n");
    }

    // col labels
    printf("     ");
    for (int c = 0; c < size; c++) printf("%2d  ", c+1);
    printf("\n\n");
}

void printLegend(void) {
    puts(" Legend:");
    puts("  > ^ v <  : LRRH (you)");
    puts("  P: Pit    F: Flower    B: Bakeshop");
    puts("  W: Wolf   M: Woodsman   G: Granny\n");
}

void placeElement(char grid[][MAX_SIZE],
                  int row, int col,
                  char symbol)
{
    grid[row][col] = symbol;
}

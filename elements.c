#include <stdio.h>
#include "headers/elements.h"

// generic prompt function
static void promptCoord(const char *label, int idx, int GridSize, int *r, int *c, int used[][MAX_SIZE]) {
    int row, col;
    do {
        printf("Coordinates of %s #%d (row col): ", label, idx+1);
        scanf("%d%d", &row, &col);
        if (row<1||row>GridSize||col<1||col>GridSize||used[row-1][col-1]) {
            printf("\tinvalid or occupied; try again\n");
        } else break;
    } while (1);
    used[row-1][col-1] = 1;
    *r = row; *c = col;
}

void GetValidPitLoc(int i,int G,int*x,int*y,int u[][MAX_SIZE]) {
    promptCoord("Pit",i,G,x,y,u);
}
void GetValidFlowerLoc(int i,int G,int*x,int*y,int u[][MAX_SIZE]) {
    promptCoord("Flower",i,G,x,y,u);
}
void GetValidBakeshopLoc(int i,int G,int*x,int*y,int u[][MAX_SIZE]) {
    promptCoord("Bakeshop",i,G,x,y,u);
}
void GetValidWolfLoc(int G,int*x,int*y,int u[][MAX_SIZE]) {
    promptCoord("Wolf",0,G,x,y,u);
}
void GetValidWoodsmanLoc(int G,int*x,int*y,int u[][MAX_SIZE]) {
    promptCoord("Woodsman",0,G,x,y,u);
}
void GetValidGrannyLoc(int G,int*x,int*y,int u[][MAX_SIZE]) {
    promptCoord("Granny",0,G,x,y,u);
}

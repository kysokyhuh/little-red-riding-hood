#include <stdio.h>
#include "headers/elements.h"
#include "headers/agent.h"
#include "headers/grid.h"
#include "headers/utils.h"

#define MAX_SIZE 15

int main() {
    int gridSize;
    do {
        printf("Please enter the grid size (8 to 15): ");
        scanf("%d", &gridSize);
    } while (gridSize < 8 || gridSize > 15);

    char grid[MAX_SIZE][MAX_SIZE];
    initGrid(grid, gridSize);

    int used[MAX_SIZE][MAX_SIZE] = {0};

    // Pits
    int px[3], py[3], pits;
    printf("\nNumber of pits (0–3): ");
    scanf("%d", &pits);
    if (pits < 0) pits = 0;
    if (pits > 3) pits = 3;
    for (int i = 0; i < pits; i++) {
        GetValidPitLoc(i, gridSize, &px[i], &py[i], used);
        placeElement(grid, px[i], py[i], 'P');
    }

    // Flowers
    int fx[3], fy[3], flowers;
    printf("\nNumber of flowers (0–3): ");
    scanf("%d", &flowers);
    if (flowers < 0) flowers = 0;
    if (flowers > 3) flowers = 3;
    for (int i = 0; i < flowers; i++) {
        GetValidFlowerLoc(i, gridSize, &fx[i], &fy[i], used);
        placeElement(grid, fx[i], fy[i], 'F');
    }

    // Bakeshops
    int bx[3], by[3], shops;
    printf("\nNumber of bakeshops (0–3): ");
    scanf("%d", &shops);
    if (shops < 0) shops = 0;
    if (shops > 3) shops = 3;
    for (int i = 0; i < shops; i++) {
        GetValidBakeshopLoc(i, gridSize, &bx[i], &by[i], used);
        placeElement(grid, bx[i], by[i], 'B');
    }

    // Wolf
    int wx, wy;
    GetValidWolfLoc(gridSize, &wx, &wy, used);
    placeElement(grid, wx, wy, 'W');

    // Woodsman
    int mx, my;
    GetValidWoodsmanLoc(gridSize, &mx, &my, used);
    placeElement(grid, mx, my, 'M');

    // Granny
    int gx, gy;
    GetValidGrannyLoc(gridSize, &gx, &gy, used);
    placeElement(grid, gx, gy, 'G');

    printf("\nStarting simulation...\n");

    // LRRH state
    int lrrhx = 0, lrrhy = 0;
    char direction = 'R';      // initial facing
    int bread = 0, flowerCollected = 0, hasWoodsman = 0;
    int moves = 0, rotates = 0;
    char sensed = 'n';

    // Tracking first‐pickup stats: (x,y) and move index
    int fx0 = -1, fy0 = -1, fMove = -1;
    int bx0 = -1, by0 = -1, bMove = -1;
    int wx0 = -1, wy0 = -1, wMove = -1;

    while (1) {
        displayGrid(grid, gridSize, lrrhx, lrrhy, direction);
        printLegend();

        // printStats signature updated to take:
        // (moves, lastSense, rotates,
        //  fx, fy, fMove,  bx, by, bMove,  wx, wy, wMove)
        printStats(moves, sensed, rotates,
                   fx0, fy0, fMove,
                   bx0, by0, bMove,
                   wx0, wy0, wMove);

        waitForEnter();

        // Sense what's ahead
        sensed = sense(direction, lrrhx, lrrhy, grid, gridSize);

        // Move + encounter logic
        int done = moveLRRH(&lrrhx, &lrrhy, &direction,
                            grid, gridSize,
                            &bread, &flowerCollected, &hasWoodsman,
                            sensed, &moves, &rotates);

        // Record first-time pickups
        if (flowerCollected && fMove < 0) {
            fx0 = lrrhx;
            fy0 = lrrhy;
            fMove = moves;
        }
        if (bread && bMove < 0) {
            bx0 = lrrhx;
            by0 = lrrhy;
            bMove = moves;
        }
        if (hasWoodsman && wMove < 0) {
            wx0 = lrrhx;
            wy0 = lrrhy;
            wMove = moves;
        }

        if (done) {
            displayResult(bread, flowerCollected, hasWoodsman);
            break;
        }
    }

    return 0;
}

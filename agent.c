#include <stdio.h>
#include <stdlib.h>   // rand(), srand()
#include <time.h>     // time()
#include "headers/agent.h"

//
// Helper: is the square one step ahead impassable?
//   - off the grid
//   - a pit ('P')
//   - a wolf ('W')
//
static int isBlocked(char dir,
                     int x, int y,
                     char grid[][MAX_SIZE],
                     int size)
{
    int nx = x, ny = y;
    switch (dir) {
      case 'U': nx--; break;
      case 'D': nx++; break;
      case 'L': ny--; break;
      case 'R': ny++; break;
    }
    if (nx < 0 || ny < 0 || nx >= size || ny >= size) return 1;
    if (grid[nx][ny] == 'P') return 1;
    if (grid[nx][ny] == 'W') return 1;
    return 0;
}

void rotateDirection(char *dir) {
    switch (*dir) {
      case 'U': *dir = 'R'; break;
      case 'R': *dir = 'D'; break;
      case 'D': *dir = 'L'; break;
      case 'L': *dir = 'U'; break;
    }
}

char sense(char direction,
           int x, int y,
           char grid[][MAX_SIZE],
           int size)
{
    int nx = x, ny = y;
    switch (direction) {
      case 'U': nx--; break;
      case 'D': nx++; break;
      case 'L': ny--; break;
      case 'R': ny++; break;
    }
    if (nx < 0 || ny < 0 || nx >= size || ny >= size)
        return 'n';
    switch (grid[nx][ny]) {
      case 'P': return 'b';
      case 'W': return 'h';
      case 'F': return 'c';
      case 'B': return 'd';
      case 'M': return 's';
      case 'G': return 'l';
      default:  return 'n';
    }
}

int moveLRRH(int *x, int *y, char *dir,
             char grid[][MAX_SIZE], int size,
             int *bread, int *flower, int *hasWoodsman,
             char sensed, int *moveCount, int *rotateCount)
{
    // Seed RNG once
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned)time(NULL));
        seeded = 1;
    }

    // 1) Priority: go to any adjacent still-needed target (Up, Left, Right, Down)
    const char prioDirs[4] = {'U','L','R','D'};
    const int  dX[4] = {-1, 0,  0, +1};
    const int  dY[4] = { 0,-1, +1,  0};

    for (int i = 0; i < 4; i++) {
        int tx = *x + dX[i];
        int ty = *y + dY[i];
        if (tx < 0 || ty < 0 || tx >= size || ty >= size) continue;
        char c = grid[tx][ty];
        // if it's a flower we still need:
        if (c == 'F' && !*flower) {
            char targetDir = prioDirs[i];
            while (*dir != targetDir) {
                rotateDirection(dir);
                (*rotateCount)++;
            }
            *x = tx; *y = ty;
            (*moveCount)++;
            *flower = 1;
            printf("\n\tLRRH picked a flower.\n");
            return 0;
        }
        // if it's a bakeshop we still need:
        if (c == 'B' && !*bread) {
            char targetDir = prioDirs[i];
            while (*dir != targetDir) {
                rotateDirection(dir);
                (*rotateCount)++;
            }
            *x = tx; *y = ty;
            (*moveCount)++;
            *bread = 1;
            printf("\n\tLRRH bought bread.\n");
            return 0;
        }
        // if it's the woodsman we still need:
        if (c == 'M' && !*hasWoodsman) {
            char targetDir = prioDirs[i];
            while (*dir != targetDir) {
                rotateDirection(dir);
                (*rotateCount)++;
            }
            *x = tx; *y = ty;
            (*moveCount)++;
            *hasWoodsman = 1;
            printf("\n\tLRRH met the Woodsman.\n");
            return 0;
        }
    }

    // 2) No immediate target → choose randomly among valid moves
    //
    //    but if the square is 'G' and not fully prepared, skip it
    //
    char cand[4] = {'U','R','D','L'};
    int good[4], nGood = 0;
    for (int i = 0; i < 4; i++) {
        char d = cand[i];
        if (isBlocked(d, *x, *y, grid, size)) continue;

        // compute candidate cell
        int nx = *x, ny = *y;
        switch (d) {
          case 'U': nx--; break;
          case 'D': nx++; break;
          case 'L': ny--; break;
          case 'R': ny++; break;
        }
        // if it's Granny but not fully prepared, skip
        if (grid[nx][ny] == 'G' && !(*bread && *flower && *hasWoodsman))
            continue;

        good[nGood++] = i;
    }

    if (nGood == 0) {
        printf("\n\tLRRH is trapped! YOU LOSE.\n");
        return 1;
    }

    // pick one at random
    int pick = good[rand() % nGood];
    char newDir = cand[pick];
    while (*dir != newDir) {
        rotateDirection(dir);
        (*rotateCount)++;
    }

    // step forward
    int nx = *x, ny = *y;
    switch (*dir) {
      case 'U': nx--; break;
      case 'D': nx++; break;
      case 'L': ny--; break;
      case 'R': ny++; break;
    }
    char cell = grid[nx][ny];

    // handle wolf
    if (cell == 'W') {
        if (*bread) {
            printf("\n\tThe Wolf ate your bread and let you pass.\n");
            *bread = 0;
        } else {
            printf("\n\tThe Wolf ate LRRH. GAME OVER.\n");
            return 1;
        }
    }
    // flower pickup
    if (cell == 'F' && !*flower) {
        printf("\n\tLRRH picked a flower.\n");
        *flower = 1;
    }
    // bread pickup
    if (cell == 'B' && !*bread) {
        printf("\n\tLRRH bought bread.\n");
        *bread = 1;
    }
    // woodsman pickup
    if (cell == 'M' && !*hasWoodsman) {
        printf("\n\tLRRH met the Woodsman.\n");
        *hasWoodsman = 1;
    }
    // granny encounter (only possible if fully prepared)
    if (cell == 'G') {
        printf("\n\tGranny welcomes you — YOU WIN! 🎉\n");
        return 1;
    }

    // commit move
    *x = nx; *y = ny;
    (*moveCount)++;
    return 0;
}

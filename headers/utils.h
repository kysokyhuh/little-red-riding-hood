#ifndef UTILS_H
#define UTILS_H

/**
 * Pause until the user presses ENTER.
 */
void waitForEnter(void);

/**
 * Print overall stats plus pickup details.
 *
 * @param moves   total moves made so far
 * @param senses  last sense() return value
 * @param rotates total rotations made so far
 * @param fx,fy,fm  row, col, and move# when Flower was first picked (or fx<0 if not yet)
 * @param bx,by,bm  same for Bread
 * @param wx,wy,wm  same for Woodsman
 */
void printStats(int moves, int senses, int rotates,
                int fx, int fy, int fm,
                int bx, int by, int bm,
                int wx, int wy, int wm);

/**
 * Final game summary.
 *
 * @param bread        non-zero if Bread was picked
 * @param flower       non-zero if Flower was picked
 * @param hasWoodsman  non-zero if Woodsman was picked
 */
void displayResult(int bread, int flower, int hasWoodsman);

#endif // UTILS_H

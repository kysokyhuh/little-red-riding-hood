// headers/agent.h
#ifndef AGENT_H
#define AGENT_H

#include "grid.h"    // for MAX_SIZE

// Rotate facing direction clockwise (U→R→D→L→U).
void rotateDirection(char *dir);

// Sense what's directly in front of LRRH:
//  'b' = breeze (pit), 'h' = howl (wolf), 'c' = scent (flower),
//  'd' = heat (bakeshop), 's' = sound (woodsman), 'l' = light (granny),
//  'n' = nothing (or out-of-bounds).
char sense(char direction,
           int x, int y,
           char grid[][MAX_SIZE],
           int size);

// Move LRRH one step.  Returns 1 if the game ends (win or lose), 0 otherwise.
//
// • First checks the four adjacent cells (Up/Left/Right/Down) for any
//   *still-needed* target (flower, bread, woodsman), and if found,
//   goes there immediately.
// • Otherwise picks a random valid direction (never off-grid, into P or W).
// • Collects F/B/M on arrival, or resolves wolf encounter.
// • Only enters G when fully prepared.
//
// Arguments:
//   x,y           pointers to current LRRH coords
//   dir           pointer to current facing ('U','R','D','L')
//   grid,size     your world + its size
//   bread,flower,hasWoodsman  your three flags
//   sensed        last sense() result (for stats display)
//   moveCount,rotateCount     your stats counters
int moveLRRH(int *x, int *y, char *dir,
             char grid[][MAX_SIZE], int size,
             int *bread, int *flower, int *hasWoodsman,
             char sensed, int *moveCount, int *rotateCount);

#endif // AGENT_H

#ifndef ELEMENTS_H
#define ELEMENTS_H

#define MAX_SIZE 15

void GetValidPitLoc(int index, int GridSize, int *x, int *y, int used[][MAX_SIZE]);
void GetValidFlowerLoc(int index, int GridSize, int *x, int *y, int used[][MAX_SIZE]);
void GetValidBakeshopLoc(int index, int GridSize, int *x, int *y, int used[][MAX_SIZE]);
void GetValidWolfLoc(int GridSize, int *x, int *y, int used[][MAX_SIZE]);
void GetValidWoodsmanLoc(int GridSize, int *x, int *y, int used[][MAX_SIZE]);
void GetValidGrannyLoc(int GridSize, int *x, int *y, int used[][MAX_SIZE]);

#endif

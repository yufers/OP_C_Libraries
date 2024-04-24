#ifndef LAB_THREAD_IO_H
#define LAB_THREAD_IO_H

#include <stdio.h>
#include <stdlib.h>

void printMatrix(int *matrix, int n, int m);


void fill_matrix(int *matrix, int sizeOfMatrix, int *query, int queryCount);

int countNeighbors(int *matrix, size_t n, size_t m, size_t col, size_t row);
void liveGame(int *matrix, size_t n, size_t m);

void MedianFilter(int *matrix, int filter);

#endif //LAB_THREAD_IO_H

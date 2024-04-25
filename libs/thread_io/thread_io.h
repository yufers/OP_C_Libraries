#ifndef LAB_THREAD_IO_H
#define LAB_THREAD_IO_H

#include <stdio.h>
#include <stdlib.h>

int compareInts1(const void *intPtr1, const void *intPtr2);
void printMatrix(int *matrix, int n, int m);

void fill_matrix(int *matrix, int sizeOfMatrix, int *query, int queryCount);

int countNeighbors(int *matrix, size_t n, size_t m, size_t col, size_t row);
void liveGame(int *matrix, size_t n, size_t m);

int calculateMedianVector(int *matrix, int max_col, int row, int col, int *arrayOfNums, int filter_size);
void medianFilter(int *matrix, int filter, int n, int m);

#endif //LAB_THREAD_IO_H

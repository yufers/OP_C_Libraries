#ifndef LAB_THREAD_IO_H
#define LAB_THREAD_IO_H

#include <stdio.h>
#include <stdlib.h>
#include "../string/tasks/string_.h"
#include "../data_structures/vector/vectorVoid.h"
#include "../data_structures/matrix/matrix.h"
#include "../file_io/file_io.h"

typedef struct DomainRecord {
    long counter;
    WordDescriptor domain;
} DomainRecord;

typedef struct DomainCounter {
    long counter;
    char domain[255];
} DomainCounter;

typedef struct TreeItem {
    int level;
    int value;
    int type;
    int idx;
} TreeItem;

int compareInts1(const void *intPtr1, const void *intPtr2);
void printMatrix(int *matrix, int n, int m);

void fill_matrix(int *matrix, size_t sizeOfMatrix, int *query, size_t queryCount);

int countNeighbors(int *matrix, int n, int m, int col, int row);
void liveGame(int *matrix, size_t n, size_t m);

int calculateMedianVector(int *matrix, int max_col, int row, int col, int *arrayOfNums, int filter_size);
void medianFilter(int *matrix, int filter, int n, int m);

int compareWordDescriptors(const void *wordPtr1, const void *wordPtr2);
vectorVoid showVisitStats(char *stats);

int submatricesNum(matrix *m);

char* minStringNum(char *pattern);

vectorVoid maxThree(int *nums, int len);

char* strShuffle(char *symbols, int *indices, int len);

size_t fileWithSmallerValues(char *fileInputPath, char *fileOutputPath, int n);

void outputFileInChunks(char *fileInputPath, int n);

#endif //LAB_THREAD_IO_H

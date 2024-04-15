#ifndef LAB_FILE_IO_H
#define LAB_FILE_IO_H

#include <stdio.h>
#include <stdlib.h>
#include "../data_structures/matrix/matrix.h"

#define MAX_LINE_SIZE 1024
extern char _fileReadBuffer[MAX_LINE_SIZE];

typedef struct athletesInfo {
    char name[256];
    int rating;
} athletesInfo;

typedef struct goodsInStockInfo {
    char name[256];
    int priceForOne;
    int totalPrice;
    int quantity;
} goodsInStockInfo;

typedef struct orderInfo {
    char name[256];
    int quantity;
} orderInfo;

typedef struct Polynomial {
    int pow;
    int k;
} Polynomial;

size_t readFileToBuff(char *filePath, char *buff, size_t buffSize);
size_t readFileBinaryToBuff(char *filePath, char *buff, size_t buffSize);

void rowsToColumnsInMatrix(char *filePath);

size_t exponentialNumToNum(char *filePath, char *fileOutputPath);

size_t saveFileWithMathematicalExpression(char *filePath, char *fileOutputPath);

size_t saveFileWithRequiredLen(char *filePath, char *fileOutputPath, char *pattern);

size_t saveFileWithLongestWord(char *filePath, char *fileOutputPath);

void removeZeroPolynomial(char *filePath, int x);

void binFileSort(char *filePath);

void nonSymetricalMatrixesInTranspose(char *filePath);

void creatingTeam(char *filePath, int neededAthletes);

void ordersInfo(char *filePath1, char *filePath2);

matrix readMatrixFromStream(FILE *fp, int n, int *res);
long getFileSize(FILE *fp);

#endif //LAB_FILE_IO_H

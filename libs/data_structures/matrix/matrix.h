#ifndef LAB_MATRIX_H
#define LAB_MATRIX_H

# include <stdint.h>
# include <stdbool.h>
# include <assert.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix *m);

void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix *m);

void outputMatrix(matrix m);

void outputMatrixSum(matrix m, bool showSum);

void inputMatrices(matrix *ms, int nMatrices);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);

void swapColumns(matrix m, int j1, int j2);

long long getSum(int *a, int n);
int getSumCol(int **values, int nRows, int n);

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int));
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int));
void insertionSortBySumMatrixInt(int *sums, matrix *ms, int n);

bool isSquareMatrix(matrix *m);

bool areTwoMatricesEqual(matrix *m1, matrix *m2);

bool isEMatrix(matrix *m);

bool isSymmetricMatrix(matrix *m);

void transposeSquareMatrix(matrix *m);

void transposeMatrix(matrix *m);

position getMinValuePos(matrix m);

position getMaxValuePos(matrix m);

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);

matrix *createArrayOfMatrixFromArray(const int *values,size_t nMatrices, size_t nRows, size_t nCols);

//=============================================================================================================

void replaceMinMax(matrix m);

int getMax(int *a, int n);
void sortRowsByMinElement(matrix m);

int getMin(int *a, int n);
void sortColsByMinElement(matrix m);

matrix mulMatrices(matrix m1, matrix m2);
void getSquareOfMatrixIfSymmetric(matrix *m);

bool isUnique(long long *a, int n);
void transposeIfMatrixHasNotEqualSumOfRows(matrix m);

bool isMutuallyInverseMatrices(matrix m1, matrix m2);
matrix createIdentityMatrix(size_t nRows, size_t nCols);

int max(int a, int b);
long long findSumOfMaxesOfPseudoDiagonal(matrix m);

int getMinInArea(matrix m, matrix m_area);

float getDistance(int *a, int n);
void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int));
void sortByDistances(matrix m);

int cmp_long_long(const void *pa, const void *pb);
int countNUnique(long long *a, int n);
int countEqClassesByRowsSum(matrix m);

int getNSpecialElement(matrix m);

position getLeftMin(matrix m);
void swapPenultimateRow(matrix m, int n);

bool isNonDescendingSorted(int *a, int n);
bool hasAllNonDescendingRows(matrix m);
int countNonDescendingRowsMatrices(matrix *ms, int nMatrix);

int countValues(const int *a, int n, int value);
int countZeroRows(matrix m);
void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix);

int getMatrixNorma(matrix m);
void printMatrixWithMinNorma(matrix *ms, int nMatrix);

int min2(int a, int b);
int getNSpecialElement2(matrix m);

double getScalarProduct(int *a, int *b, int n);
double getVectorLength(int *a, int n);
double getCosine(int *a, int *b, int n);
int getVectorIndexWithMaxAngle(matrix m, int *b);

long long getScalarProductRowAndCol(matrix m, int i, int j);
long long getSpecialScalarProduct(matrix m, int n);

#endif //LAB_MATRIX_H

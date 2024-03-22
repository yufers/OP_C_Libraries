#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "matrix.h"

int compare(const void *a, const void *b) {
    int int_a = *((int *) a);
    int int_b = *((int *) b);

    if (int_a == int_b) return 0;
    else if (int_a < int_b) return -1;
    else return 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_matrix(int *a, int *b, matrix *m, int col1, int col2) {
    swap(a, b);

    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];

        int temp2 = row[col1];
        row[col1] = row[col2];
        row[col2] = temp2;
    }
}


void insertionSortBySumRowsInt(int *rows, matrix *m) {
    for (size_t i = 1; i < m->nRows; i++) {
        int t = rows[i];
        int *row = m->values[i];
        int j = i;
        while (j > 0 && rows[j - 1] > t) {
            rows[j] = rows[j - 1];
            m->values[j] = m->values[j - 1];
            j--;
        }
        rows[j] = t;
        m->values[j] = row;
    }
}

void insertionSortBySumMatrixInt(int *sums, matrix *ms, int n) {
    for (size_t i = 1; i < n; i++) {
        int t = sums[i];
        matrix m = ms[i];
        int j = i;
        while (j > 0 && sums[j - 1] > t) {
            sums[j] = sums[j - 1];
            ms[j] = ms[j - 1];
            j--;
        }
        sums[j] = t;
        ms[j] = m;
    }
}

void insertionSortBySumRowsFloat(float *rows, matrix *m) {
    for (size_t i = 1; i < m->nRows; i++) {
        float t = rows[i];
        int *row = m->values[i];
        int j = i;
        while (j > 0 && rows[j - 1] > t) {
            rows[j] = rows[j - 1];
            m->values[j] = m->values[j - 1];
            j--;
        }
        rows[j] = t;
        m->values[j] = row;
    }
}

void selectionSortBySumCols(int *a, matrix *m) {
    for (int i = 0; i < m->nCols - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < m->nCols; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap_matrix(&a[i], &a[minPos], m, i, minPos);
    }
}

//--------------------------------------------------------------

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }

    free(m->values);

    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &row[j]);
        }
    }
}

void outputMatrix(matrix m) {
    outputMatrixSum(m, false);
}

void outputMatrixSum(matrix m, bool showSum) {
    for (int i = 0; i < m.nRows; i++) {
        int sum = 0;
        for (int j = 0; j < m.nCols; j++) {
            printf("%d\t", m.values[i][j]);
            sum += m.values[i][j];
        }
        if (showSum) {
            printf("=%d\n", sum);
        } else {
            printf("\n");
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int a = 0; a < nMatrices; a++) {
        inputMatrix(&ms[a]);
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int a = 0; a < nMatrices; a++) {
        outputMatrix(ms[a]);
        printf("\n");
    }
}

void swapRows(matrix m, int i1, int i2) {
    if ((i1 >= m.nRows) || (i2 >= m.nRows)) {
        fprintf(stderr, "matrix index out of bounds");
        exit(1);
    }

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nCols; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

int getSumCol(int **values, int nRows, int n) {
    int sum = 0;
    for (int i = 0; i < nRows; i++) {
        int *row = values[i];
        sum += row[n];
    }
    return sum;
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        int sum = criteria(m.values[i], m.nCols);
        arr[i] = sum;
    }
    insertionSortBySumRowsInt(arr, &m);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    bool debug = false;
    int arr[m.nCols];

    for (int i = 0; i < m.nCols; i++) {
        int col[m.nRows];

        for (int j = 0; j < m.nRows; j++) {
            int *row = m.values[j];
            col[j] = row[i];
        }

        int sum = criteria(col, m.nRows);
        arr[i] = sum;
        if (debug) {
            printf("%d\t", sum);
        }
    }
    if (debug) {
        printf("\n");
    }
    selectionSortBySumCols(arr, &m);
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows) {
        return false;
    }
    if (m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        int *row1 = m1->values[i];
        int *row2 = m2->values[i];

        int res = memcmp(row1, row2, sizeof(int) * m1->nCols);

        if (res) {
            return false;
        }
    }
    return true;
}

bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];
        for (int j = 0; j < m->nCols; j++) {
            if (i == j) {
                if (row[j] != 1) {
                    return false;
                }
            } else {
                if (row[j] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void transposeSquareMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i; j < m->nCols; j++) {
            if (i != j) {
                swap(&m->values[i][j], &m->values[j][i]);
            }
        }
    }
}

void transposeMatrix(matrix *m) {
    matrix m_new = getMemMatrix(m->nCols, m->nRows);

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            m_new.values[j][i] = m->values[i][j];
        }
    }
    freeMemMatrix(m);
    *m = m_new;
}

position getMinValuePos(matrix m) {
    position pos = {-1, -1};

    int min = INT_MAX;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }
        }
    }
    return pos;
}

position getMaxValuePos(matrix m) {
    position pos = {1, 1};

    int max = INT_MIN;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }
        }
    }
    return pos;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {

    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = a[k++];
        }
    }
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}

//=============================================================================================================

void replaceMinMax(matrix m) {
    int max = INT_MIN;
    int min = INT_MAX;
    int maxI = 0;
    int minI = 0;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                minI = i;
            }
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                maxI = i;
            }
        }
    }
    swapRows(m, maxI, minI);
}

int getMax(int *a, int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

void sortRowsByMinElement(matrix m) {
    int arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        int max = getMax(m.values[i], m.nCols);
        arr[i] = max;
    }
    insertionSortBySumRowsInt(arr, &m);
}

int getMin(int *a, int n) {
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

void sortColsByMinElement(matrix m) {
    int arr[m.nCols];

    for (int i = 0; i < m.nCols; i++) {
        int col[m.nRows];

        for (int j = 0; j < m.nRows; j++) {
            int *row = m.values[j];
            col[j] = row[i];
        }

        int sum = getMin(col, m.nRows);
        arr[i] = sum;
    }
    selectionSortBySumCols(arr, &m);
}

matrix mulMatrices(matrix m1, matrix m2) {
    matrix m_new = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            m_new.values[i][j] = 0;

            for (int k = 0; k < m2.nRows; k++) {
                m_new.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return m_new;
}


void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (m->nRows != m->nCols) {
        fprintf(stderr, "Not Symmetric");
        exit(1);
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                fprintf(stderr, "Not Symmetric");
                exit(1);
            }
        }
    }
    matrix m3 = mulMatrices(*m, *m);

    freeMemMatrix(m);
    *m = m3;
}

bool isUnique(long long *a, int n) {
    qsort(a, n, sizeof(long long), compare);

    int temp = 0;
    for (int i = 0; i < n; i++) {
        if (a[i + 1] == a[i]) {
            return false;
        }
    }
    return true;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        long long sum = getSum(m.values[i], m.nCols);
        arr[i] = sum;
    }
    bool res = isUnique(arr, m.nRows);

    if (res) {
        transposeSquareMatrix(&m);
    } else {
        fprintf(stderr, "Not Unique");
        exit(1);
    }
}

matrix createIdentityMatrix(size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (i == j) {
                m.values[i][j] = 1;
            } else {
                m.values[i][j] = 0;
            }
        }
    }
    return m;
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix m_identity = createIdentityMatrix(m2.nRows, m2.nCols);
    matrix m_Inverse = mulMatrices(m2, m_identity);
    bool res = areTwoMatricesEqual(&m1, &m_Inverse);

    if (res) {
        return true;
    } else {
        return false;
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int arr[m.nCols + m.nRows - 2];
    int res;
    int z = 0;
    int sum = 0;

    for (int k = 1; k < m.nCols; k++) {
        res = INT_MIN;
        for (int i = 0, j = k; i < m.nRows && j < m.nCols; i++, j++) {
            res = max(res, m.values[i][j]);

        }
        arr[z++] = res;
    }

    for (int k = 1; k < m.nRows; k++) {
        res = INT_MIN;
        for (int i = k, j = 0; i < m.nRows && j < m.nCols; i++, j++) {
            res = max(res, m.values[i][j]);
        }
        arr[z++] = res;
    }

    for (int x = 0; x < m.nCols + m.nRows - 2; x++) {
        sum += arr[x];
    }
    return sum;
}

int getMinInArea(matrix m, matrix m_area) {
    int min = INT_MAX;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m_area.values[i][j] == 1 && m.values[i][j] < min) {
                min = m.values[i][j];
            }
        }
    }
    return min;
}

float getDistance(int *a, int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum = sum + (a[i] * a[i]);
    }
    return (float) sqrt(sum);
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    float arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        arr[i] = criteria(m.values[i], m.nRows);
    }

    insertionSortBySumRowsFloat(arr, &m);
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

int cmp_long_long(const void *pa, const void *pb) {
    return (long long) pa == (long long) pb;
}

int countNUnique(long long *a, int n) {
    int counter = 0;
    long long res = 0;

    for (int i = 0; i < n; i++) {
        res = cmp_long_long((const void *) a[i + 1], (const void *)a[i]);

        if (!res) {
            counter++;
        }
    }
    return counter;
}

int countEqClassesByRowsSum(matrix m) {
    long long arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        long long sum = 0;
        for (int j = 0; j < m.nCols; j++) {
            sum += m.values[i][j];
        }
        arr[i] = sum;
    }
    qsort(&arr, m.nRows, sizeof(long long), compare);
    int res = countNUnique(arr, m.nRows);

    return res;
}

int getNSpecialElement(matrix m) {
    int counter = 0;

    for (int j = 0; j < m.nCols; j++) {
        int max = INT_MIN;
        int sum = 0;

         for (int i = 0; i < m.nRows; i++) {
            sum += m.values[i][j];

            if (m.values[i][j] > max) {
                max = m.values[i][j];
            }
        }
        if (max > sum - max) {
            counter++;
        }
    }
    return counter;
}

position getLeftMin(matrix m) {
    int min = INT_MAX;
    position res;

    for (int i = 0 ; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                res.colIndex = j;
                res.rowIndex = i;
            }
        }
    }
    return res;
}

void swapPenultimateRow(matrix m, int n) {
    position res = getLeftMin(m);

    for (int i = m.nRows - 1; i >= 0 ; i--) {
        m.values[n-2][i] = m.values[i][res.colIndex];
    }
}

bool isNonDescendingSorted(int *a, int n) {
    int counter = 0;

    for (int i = 0; i < n-1; i++) {
        if (a[i] <= a[i+1]) {
            counter++;
        }
    }
    if (counter == n-1) {
        return true;
    } else {
        return false;
    }
}

bool hasAllNonDescendingRows(matrix m) {
    int counter = 0;

    for (int i = 0; i < m.nRows; i++) {
        if (isNonDescendingSorted(m.values[i], m.nCols)) {
            counter++;
        }
    }
    if (counter == m.nRows) {
        return true;
    } else {
        return false;
    }
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int counter = 0;

    for (int i = 0; i < nMatrix; i++) {
        if (hasAllNonDescendingRows(ms[i])) {
            counter++;
        }
    }
    return counter;
}

int countValues(const int *a, int n, int value) {
    int counter = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] == value) {
            counter++;
        }
    }
    return counter;
}

int countZeroRows(matrix m) {
    int counter = 0;

    for (int i = 0; i < m.nRows; i++) {
        int res = countValues(m.values[i], m.nCols, 0);

        if (res == m.nCols) {
            counter++;
        }
    }
    return counter;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int arr[nMatrix];

    for (int i = 0; i < nMatrix; i++) {
        arr[i] = countZeroRows(ms[i]);
    }
    insertionSortBySumMatrixInt(arr, ms, nMatrix);
    int max = arr[nMatrix - 1];

    for (int j = nMatrix; j > 0; j--) {
        if (arr[j] == max) {
            outputMatrix(ms[j]);
            printf("\n");
        }
    }
}

int getMatrixNorma(matrix m) {
    int max = INT_MIN;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {

            int val = abs(m.values[i][j]);
            if (val > max) {
                max = val;
            }
        }
    }
    return max;
}

void printMatrixWithMinNorma(matrix *ms, int nMatrix) {
    int arr[nMatrix];

    for (int i = 0; i < nMatrix; i++) {
        arr[i] = getMatrixNorma(ms[i]);
    }
    insertionSortBySumMatrixInt(arr, ms, nMatrix);
    int min = arr[0];

    for (int j = 0; j < nMatrix; j++) {
        if (arr[j] == min) {
            outputMatrix(ms[j]);
            printf("\n");
        }
    }
}

int min2(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int getNSpecialElement2(matrix m) {
    int nSpecial = 0;
    int currMax;

    for (int i = 0; i < m.nRows; i++) {
        currMax = INT_MIN;
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] <= currMax) {
                currMax = max(currMax, m.values[i][j]);
                continue;
            }

            currMax = max(currMax, m.values[i][j]);

            if ((j > 0) && m.values[i][j] <= m.values[i][j - 1]) {
                continue;
            }

            if ((j+1 < m.nCols) && (m.values[i][j] >= m.values[i][j+1])) {
                continue;
            }

            int min = INT_MAX;
            for (int k = j + 1; k < m.nCols; k++) {
                min = min2(min, m.values[i][k]);
            }

            if (m.values[i][j] >= min) {
                continue;
            }


        nSpecial++;

        }
    }
    return nSpecial;
}

double getScalarProduct(int *a, int *b, int n) {
    double mul = 0;

    for (int i = 0; i < n; i++) {
        mul += a[i] * b[i];
    }
    return mul;
}

double getVectorLength(int *a, int n) {
    double sum = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i] * a[i];
    }
    return sqrt(sum);
}

double getCosine(int *a, int *b, int n) {
    double cos = getScalarProduct(a, b, n) / (getVectorLength(a, n) * getVectorLength(b, n));
    return cos;
}

int getVectorIndexWithMaxAngle(matrix m, int *b) {
    double res = DBL_MAX;
    int idx = 0;

    for (int i = 0; i < m.nRows; i++) {
        double cur_res = getCosine(m.values[i], b, m.nRows);

        if (cur_res < res) {
            res = cur_res;
            idx = i;
        }
    }
    return idx;
}

long long getScalarProductRowAndCol(matrix m, int i, int j) {
    long long sum = 0;

    for (int k = 0; k < m.nRows; k++) {
        sum += m.values[i][k] * m.values[k][j];
    }
    return sum;
}

long long getSpecialScalarProduct(matrix m, int n) {
    int rowNum = 0;
    int colNum = 0;
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                colNum = j;
            }
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                rowNum = i;
            }
        }
    }
    long long res = getScalarProductRowAndCol(m, rowNum, colNum);
    return res;
}
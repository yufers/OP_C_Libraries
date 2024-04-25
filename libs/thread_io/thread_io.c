#include <stdio.h>
#include <stdlib.h>

int compareInts1(const void *intPtr1, const void *intPtr2) {
    int *num1 = (int *)intPtr1;
    int *num2 = (int *)intPtr2;

    return *num2 - *num1;
}

void printMatrix(int *matrix, int n, int m) {
    int (*tempMatrix)[m] = (int (*)[m])matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d\t", tempMatrix[i][j]);
        }
        printf("\n");
    }
}

void fill_matrix(int *matrix, size_t sizeOfMatrix, int *query, size_t queryCount) {
    int (*tempMatrix)[sizeOfMatrix] = (int (*)[sizeOfMatrix])matrix;
    int (*tempQuery)[4] = (int (*)[4])query;

    for (int i = 0; i < queryCount; i++) {
        int *curQuery = tempQuery[i];

        for (int row = curQuery[0]; row <= curQuery[2]; row++) {
            for (int col = curQuery[1]; col <= curQuery[3]; col++) {
                tempMatrix[row][col]++;
            }
        }
    }
}

int countNeighbors(int *matrix, int n, int m, int col, int row) {
    int (*tempMatrix)[m] = (int (*)[m])matrix;
    int row1 = row - 1;
    int row2 = row + 1;
    int col1 = col - 1;
    int col2 = col + 1;

    row1 = row1 < 0 ? 0 : row1;
    row2 = row2 >= n ? n - 1 : row2;
    col1 = col1 < 0 ? 0 : col1;
    col2 = col2 >= m ? m - 1 : col2;

    int counter = 0;
    for (int i = row1; i <= row2; i++) {
        for (int j = col1; j <= col2; j++) {
            if ((i == row) && (j == col)) {
                continue;
            }

            counter += tempMatrix[i][j];
        }
    }
    return counter;
}

void liveGame(int *matrix, size_t n, size_t m) {
    int (*tempMatrix)[m] = (int (*)[m])matrix;
    int sums[n][m];
    int (*tempMatrix1)[m] = (int (*)[m])sums;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            int res = countNeighbors(matrix, n,  m, col, row);
            sums[row][col] = res;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tempMatrix[i][j] == 1 && tempMatrix1[i][j] < 2) {
                tempMatrix[i][j] = 0;
            }
            if (tempMatrix[i][j] == 1 && (tempMatrix1[i][j] == 2 || tempMatrix1[i][j] == 3)) {
                tempMatrix[i][j] = 1;
            }
            if (tempMatrix[i][j] == 1 && tempMatrix1[i][j] > 3) {
                tempMatrix[i][j] = 0;
            }
            if (tempMatrix[i][j] == 0 && tempMatrix1[i][j] == 3) {
                tempMatrix[i][j] = 1;
            }
        }
    }
}

int calculateMedianVector(int *matrix, int max_col, int row, int col, int *arrayOfNums, int filter_size) {
    int (*tempMatrix)[max_col] = (int (*)[max_col])matrix;
    int k = 0;

    for (int i = row; i < row + filter_size; i++) {
        for (int j = col; j < col + filter_size; j++) {
            arrayOfNums[k++] = tempMatrix[i][j];
        }
    }
    qsort(arrayOfNums, k, sizeof(int), compareInts1);
    int res = arrayOfNums[((filter_size * filter_size) - 1) / 2];

    return res;
}

void medianFilter(int *matrix, int filter, int n, int m) {
    int (*tempMatrix)[m] = (int (*)[m])matrix;
    int arrayOfNums[filter * filter];
    int arrOfMedians[filter * filter];


    // Calculate median values
    int value = 0;
    int i = 0;
    for (int row = 0; row <= n - filter; row++) {
        for (int col = 0; col <= m - filter; col++) {
            value = calculateMedianVector(matrix, m, row, col, arrayOfNums, filter);
            arrOfMedians[i++] = value;
        }
    }

    // Fill median values
    i = 0;
    int ofset = (filter - 1) / 2;
    for (int row = ofset; row <= n - filter + ofset; row++) {
        for (int col = ofset; col <= m - filter + ofset; col++) {
            tempMatrix[row][col] = arrOfMedians[i++];
        }
    }
}
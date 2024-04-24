#include <stdio.h>
#include <assert.h>
#include "thread_io.h"
#include "thread_io_test.h"

void testAll_fill_matrix() {
    int n = 3;
    int count_query = 2;
    int matrix[n][n];

    int query[2][4] = {{1,1,2,2}, {0,0,1,1}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    fill_matrix(*matrix, n, *query, count_query);
    int resMatrix[3][3] = {{1,1,0}, {1,2,1}, {0,1,1}};

    for (int z = 0; z < n; z++) {
        for (int x = 0; x < n; x++) {
            assert(matrix[z][x] == resMatrix[z][x]);
        }
    }
}

void testAll_liveGame() {
    int n = 4;
    int m = 3;
    int matrix[4][3] = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};

    liveGame(*matrix, n, m);

    int resMatrix[4][3] = {{0,0,0},{1,0,1},{0,1,1},{0,1,0}};
    for (int z = 0; z < n; z++) {
        for (int x = 0; x < m; x++) {
            assert(matrix[z][x] == resMatrix[z][x]);
        }
    }
}

void testAll_MedianFilter() {

}

void testThreadAll() {
    testAll_fill_matrix();
    testAll_liveGame();
    testAll_MedianFilter();
}
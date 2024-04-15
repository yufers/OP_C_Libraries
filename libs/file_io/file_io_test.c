#include <stdio.h>
#include <assert.h>
#include "file_io.h"
#include "file_io_test.h"
#include "../string/string_test.h"
#include "../string/tasks/string_.h"

char testBuff[MAX_LINE_SIZE];

void testAll_rowsToColumnsInMatrix() {
    FILE *fp = fopen ("file_test1.txt", "w+");

    fprintf(fp, "%d\n", 5);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            fprintf(fp, "%d%d ", i, j);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    rowsToColumnsInMatrix("file_test1.txt");
    size_t fileSize = readFileToBuff("file_test1.txt", testBuff, sizeof(testBuff));
    assert(fileSize == 82);

    ASSERT_STRING("5\n"
                  "11 21 31 41 51 \n"
                  "12 22 32 42 52 \n"
                  "13 23 33 43 53 \n"
                  "14 24 34 44 54 \n"
                  "15 25 35 45 55 \n", testBuff)
}

void testAll_exponentialNumToNum() {
    FILE *fp = fopen ("file_test1.txt", "w+");

    for (int i = 0; i < 10; i++) {
        fprintf(fp, "0.%d7686878468e+%d\n", i, i);
    }
    fclose(fp);

    size_t res = exponentialNumToNum("file_test1.txt", "file_test2.txt");
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 0);
    assert(fileSize == 86);
    ASSERT_STRING("0.08\n"
                  "1.77\n"
                  "27.69\n"
                  "376.87\n"
                  "4768.69\n"
                  "57686.88\n"
                  "676868.81\n"
                  "7768688.00\n"
                  "87686880.00\n"
                  "976868800.00\n", testBuff)
}

void testAll_saveFileWithMathematicalExpression() {
    FILE *fp = fopen ("file_test1.txt", "w+");

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fprintf(fp, "2 + %d\n", i, i);
        } else if (i % 3 == 0) {
            fprintf(fp, "9 - %d * %d\n", i, i);
        } else {
            fprintf(fp, "%d + %d / 5\n", i, i);
        }
    }

    fclose(fp);

    size_t res = saveFileWithMathematicalExpression("file_test1.txt", "file_test1.txt");
    size_t fileSize = readFileToBuff("file_test1.txt", testBuff, sizeof(testBuff));
    assert(res == 10);
    assert(fileSize == 103);
    ASSERT_STRING("2 + 0\n"
                  "1 + 1 / 5\n"
                  "2 + 2\n"
                  "9 - 3 * 3\n"
                  "2 + 4\n"
                  "5 + 5 / 5\n"
                  "2 + 6\n"
                  "7 + 7 / 5\n"
                  "2 + 8\n"
                  "9 - 9 * 9\n"
                  "2\n"
                  "1\n"
                  "4\n"
                  "0\n"
                  "6\n"
                  "6\n"
                  "8\n"
                  "8\n"
                  "10\n"
                  "-72\n", testBuff)
}

void testAll_saveFileWithRequiredLen() {
    FILE *fp = fopen ("file_test1.txt", "w+");
    char word[4] = "bot";

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fputs("bot vdg uy\n", fp);
        } else if (i % 3 == 0) {
            fputs("rama ho isz\n", fp);
        } else {
            fputs("1z i7 bj\n", fp);
        }
    }
    fclose(fp);

    size_t res = saveFileWithRequiredLen("file_test1.txt", "file_test2.txt", word);
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 5);
    assert(fileSize == 19);
    ASSERT_STRING("bot bot bot bot bot", testBuff)
}

void testAll_saveFileWithLongestWord() {
    FILE *fp = fopen ("file_test1.txt", "w+");

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fputs("anton hg jui\n", fp);
        } else if (i % 3 == 0) {
            fputs("bhy gamma po\n", fp);
        } else {
            fputs("dd ll rock\n", fp);
        }
    }
    fclose(fp);

    size_t res = saveFileWithLongestWord("file_test1.txt", "file_test2.txt");
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 10);
    assert(fileSize == 56);
    ASSERT_STRING("anton rock anton gamma anton rock anton rock anton gamma", testBuff)
}

void testAll_removeZeroPolynomial() {
    FILE *fp = fopen("binary_file_test1.bin", "wb");

    int x = 4;
    Polynomial poly[] = { {3, 1},{2, 1},{1, 1},{0, 1},
                          {5, 1},{4, 2},{1, 1},{0, 2},
                          {7, 1},{5, 1},{3, 1},{0, 1},
                          {19, 1},{5, 1},{8, 1},{0, 1}};

    fwrite(poly, sizeof(Polynomial), sizeof(poly) / sizeof(Polynomial), fp);
    fclose(fp);

    removeZeroPolynomial("binary_file_test1.bin", -2);

    FILE *fd = fopen("binary_file_test1.bin", "rb");

    Polynomial res[100];

    int countRead = fread(res, sizeof(Polynomial), sizeof(res) / sizeof(Polynomial), fd);

    Polynomial expected[] = { {3, 1},{2, 1},{1, 1},{0, 1},
                          {7, 1},{5, 1},{3, 1},{0, 1},
                          {19, 1},{5, 1},{8, 1},{0, 1}};

    assert((sizeof(expected) / sizeof(Polynomial)) == countRead);
    for (int i = 0; i < countRead; i++) {
        assert(expected[i].k == res[i].k);
        assert(expected[i].pow == res[i].pow);
    }
    fclose(fd);
}

void testAll_binFileSort() {
    FILE *fp = fopen("binary_file_test1.bin", "wb");

    for (int i = 0; i < 10; i++) {
        int g = -i;
        if (i % 2 == 0) {
            fwrite(&i, sizeof(int), 1, fp);
        } else {
            fwrite(&g, sizeof(int), 1, fp);
        }
    }
    fclose(fp);

    binFileSort("binary_file_test1.bin");
    size_t fileSize = readFileBinaryToBuff("binary_file_test1.bin", testBuff, sizeof(testBuff));
    int expected[] = {8, 6, 4, 2, 0, -1, -3, -5, -7, -9};

    assert(fileSize == sizeof(expected));
    for (size_t i = 0; i < fileSize / sizeof(int); i++) {
        assert(((int *) testBuff)[i] == expected[i]);
    }
}

void testAll_nonSymetricalMatrixesInTranspose() {
    FILE *fp = fopen("binary_file_test1.bin", "wb");

    int x = 5;
    fwrite(&x, sizeof(int), 1, fp);

    int val;
    for (int z = 0; z < 10; z++) {
        if (z % 2 == 0) {
            for (int i = 1; i <= 5; i++) {
                for (int j = 1; j <= 5; j++) {
                    val = i * 10 + j;
                    fwrite(&val, sizeof(int), 1, fp);
                }
            }
        } else if (z % 3 == 0) {
            for (int i = 2; i <= 6; i++) {
                for (int j = 2; j <= 6; j++) {
                    val = i * 10 + j;
                    fwrite(&val, sizeof(int), 1, fp);
                }
            }
        } else {
            int arrSymMatr[] = {10 , 0, 5, 2, 0,
                         0, 10, 0, 5, 2,
                         5, 0, 10, 0, 5,
                         2, 5,0, 10, 0,
                         0, 2, 5, 0 ,10};
            matrix m = createMatrixFromArray(arrSymMatr, 5, 5);
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    fwrite(&m.values[i][j], sizeof(int), 1, fp);
                }
            }
            freeMemMatrix(&m);
        }
    }
    fclose(fp);

    nonSymetricalMatrixesInTranspose("binary_file_test1.bin");
    size_t fileSize = readFileBinaryToBuff("binary_file_test1.bin", testBuff, sizeof(testBuff));

    int expected[] = {5,

                      11, 21, 31, 41, 51,
                      12, 22, 32, 42, 52,
                      13, 23, 33, 43, 53,
                      14, 24, 34, 44, 54,
                      15, 25, 35, 45, 55,

                      10, 0, 5, 2, 0,
                      0, 10, 0, 5, 2,
                      5, 0, 10, 0, 5,
                      2, 5, 0, 10, 0,
                      0, 2, 5, 0, 10,

                      11, 21, 31, 41, 51,
                      12, 22, 32, 42, 52,
                      13, 23, 33, 43, 53,
                      14, 24, 34, 44, 54,
                      15, 25, 35, 45, 55,

                      22, 32, 42, 52, 62,
                      23, 33, 43, 53, 63,
                      24, 34, 44, 54, 64,
                      25, 35, 45, 55, 65,
                      26, 36, 46, 56, 66,

                      11, 21, 31, 41, 51,
                      12, 22, 32, 42, 52,
                      13, 23, 33, 43, 53,
                      14, 24, 34, 44, 54,
                      15, 25, 35, 45, 55,

                      10, 0, 5, 2, 0,
                      0, 10, 0, 5, 2,
                      5, 0, 10, 0, 5,
                      2, 5, 0, 10, 0,
                      0, 2, 5, 0, 10,

                      11, 21, 31, 41, 51,
                      12, 22, 32, 42, 52,
                      13, 23, 33, 43, 53,
                      14, 24, 34, 44, 54,
                      15, 25, 35, 45, 55,

                      10, 0, 5, 2, 0,
                      0, 10, 0, 5, 2,
                      5, 0, 10, 0, 5,
                      2, 5, 0, 10, 0,
                      0, 2, 5, 0, 10,

                      11, 21, 31, 41, 51,
                      12, 22, 32, 42, 52,
                      13, 23, 33, 43, 53,
                      14, 24, 34, 44, 54,
                      15, 25, 35, 45, 55,

                      22, 32, 42, 52, 62,
                      23, 33, 43, 53, 63,
                      24, 34, 44, 54, 64,
                      25, 35, 45, 55, 65,
                      26, 36, 46, 56, 66};

    assert(fileSize == sizeof(expected));
    for (size_t i = 0; i < fileSize / sizeof(int); i++) {
        assert(((int *) testBuff)[i] == expected[i]);
    }
}

void testAll_creatingTeam() {
    FILE *fp = fopen("binary_file_test1.bin", "wb");

    int x = 8;
    fwrite(&x, sizeof(int), 1, fp);

    athletesInfo athletes[] = {{"John Smith 5\0", 5},
                              {"John Smith 11\0", 11},
                              {"John Smith 8\0", 8},
                              {"John Smith 9\0", 9},
                               {"John Smith 6\0", 6},
                               {"John Smith 7\0", 7},
                               {"John Smith 10\0", 10},
                               {"John Smith 12\0", 12}};

    fwrite(athletes, sizeof(athletesInfo), 8, fp);

    fclose(fp);

    creatingTeam("binary_file_test1.bin", 3);

    FILE *fd = fopen("binary_file_test1.bin", "rb");
    int n;
    fread(&n, sizeof(int), 1, fd);
    athletesInfo res[n];

    int countRead = fread(res, sizeof(athletesInfo), n, fd);

    athletesInfo expectedAthletes[] = {{"John Smith 12\0", 12},
                               {"John Smith 11\0", 11},
                               {"John Smith 10\0", 10}};
    assert(3 == n);
    assert(countRead == n);
    for (int i = 0; i < countRead; i++) {
        ASSERT_STRING(expectedAthletes[i].name, res[i].name)
        assert(expectedAthletes[i].rating == res[i].rating);
    }
    fclose(fd);
}

void testAll_ordersInfo() {
    FILE *fp1 = fopen("binary_file_test1.bin", "wb");
    FILE *fp2 = fopen("binary_file_test2.bin", "wb");

    goodsInStockInfo goodsInfo[] = {{"Apples\0", 5, 100, 8},
                                    {"Beer\0", 15, 150, 30},
                                    {"carrots\0", 3, 50, 100},
                                    {"potato\0", 10, 70, 200},
                                    {"cheese\0", 40, 500, 10},
                                    {"beef\0", 100, 1000, 21}};

    orderInfo orders[] = {{"Apples\0", 5},
                          {"beef\0", 21},
                          {"carrots\0", 100},
                          {"cheese\0", 10},
                          {"potato\0", 40},
                          {"Beer\0", 21}};

    int x1 = sizeof(goodsInfo) / sizeof(goodsInStockInfo);
    fwrite(&x1, sizeof(int), 1, fp1);

    int x2 = sizeof(orders) / sizeof(orderInfo);
    fwrite(&x2, sizeof(int), 1, fp2);

    fwrite(goodsInfo, sizeof(goodsInStockInfo), x1, fp1);
    fclose(fp1);
    fwrite(orders, sizeof(orderInfo), x2, fp2);
    fclose(fp2);

    ordersInfo("binary_file_test1.bin", "binary_file_test2.bin");

    FILE *fd = fopen("binary_file_test1.bin", "rb");
    int n;
    fread(&n, sizeof(int), 1, fd);
    goodsInStockInfo res[n];

    int countRead = fread(res, sizeof(goodsInStockInfo), n, fd);

    goodsInStockInfo expected[] = {{"Apples\0", 5, 100, 3},
                                    {"Beer\0", 15, 150, 9},
                                    {"potato\0", 10, 70, 160}};
    assert((sizeof(expected) / sizeof(goodsInStockInfo)) == n);
    assert(countRead == n);
    for (int i = 0; i < countRead; i++) {
        ASSERT_STRING(expected[i].name, res[i].name)
        assert(expected[i].priceForOne == res[i].priceForOne);
        assert(expected[i].totalPrice == res[i].totalPrice);
        assert(expected[i].quantity == res[i].quantity);
    }
    fclose(fd);
}

void testFileAll() {
    testAll_rowsToColumnsInMatrix();
    testAll_exponentialNumToNum();
    testAll_saveFileWithMathematicalExpression();
    testAll_saveFileWithRequiredLen();
    testAll_saveFileWithLongestWord();
    testAll_removeZeroPolynomial();
    testAll_binFileSort();
    testAll_nonSymetricalMatrixesInTranspose();
    testAll_creatingTeam();
    testAll_ordersInfo();
}
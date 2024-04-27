#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "thread_io.h"
#include "../string/tasks/string_.h"
#include "../data_structures/vector/vectorVoid.h"



#define STATS_HEADER "cpdomains = ["
#define STATS_END "]"

int compareDomainCounterNames(const void *domainCounterPtr1, const void *domainCounterPtr2) {
    DomainRecord *domainCounter1 = (DomainRecord *)domainCounterPtr1;
    DomainRecord *domainCounter2 = (DomainRecord *)domainCounterPtr2;
    WordDescriptor word1 = domainCounter1->domain;
    WordDescriptor word2 = domainCounter2->domain;

    unsigned long len1 = word1.end - word1.begin;
    unsigned long len2 = word2.end - word2.begin;
    unsigned long min_len = len1;
    if (min_len > len2) {
        min_len = len2;
    }

    int res = memcmp(word1.begin, word2.begin, min_len);

    if (res == 0) {
        if (len1 != len2) {
            res = len1 > len2 ? 1 : -1;
        }
    }
    return res;
}

int compareInts1(const void *intPtr1, const void *intPtr2) {
    int *num1 = (int *) intPtr1;
    int *num2 = (int *) intPtr2;

    return *num2 - *num1;
}

void printMatrix(int *matrix, int n, int m) {
    int (*tempMatrix)[m] = (int (*)[m]) matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d\t", tempMatrix[i][j]);
        }
        printf("\n");
    }
}

void fill_matrix(int *matrix, size_t sizeOfMatrix, int *query, size_t queryCount) {
    int (*tempMatrix)[sizeOfMatrix] = (int (*)[sizeOfMatrix]) matrix;
    int (*tempQuery)[4] = (int (*)[4]) query;

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
    int (*tempMatrix)[m] = (int (*)[m]) matrix;
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
    int (*tempMatrix)[m] = (int (*)[m]) matrix;
    int sums[n][m];
    int (*tempMatrix1)[m] = (int (*)[m]) sums;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            int res = countNeighbors(matrix, n, m, col, row);
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
    int (*tempMatrix)[max_col] = (int (*)[max_col]) matrix;
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
    int (*tempMatrix)[m] = (int (*)[m]) matrix;
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

void parsedDomainStat(vectorVoid *data, char *start, char *end) {
    long counter = 0;

    // Проходим с начала по конец для поиска чисел
    for (char *i = start; i <= end; i++) {
        if (isdigit(*i)) {
            counter = strtol(i, &start, 10);
            break;
        }
    }

    char *endPtr = end;
    // Проходим с конца по начало для поиска доменов
    for (char *i = end; i >= start; i--) {
        if (*i == '"') {
            *endPtr = *i;
            endPtr--;
            continue;
        }
        if ((*i == '.') || (*i == ' ')) {
            WordDescriptor word = {i + 1, endPtr};
            DomainRecord domain = {counter, word};
            pushBackV(data, &domain);
        }
        if (*i == ' ') {
            break;
        }
    }
}

vectorVoid showVisitStats(char *stats) {
    // Находим начало и конец данных
    char *idxStart = strstr(stats, STATS_HEADER);
    char *idxEnd = strstr(stats, STATS_END);

    // Проверяем данные на коректоность
    if ((idxStart == NULL) || (idxEnd == NULL)) {
        fprintf(stderr, "input data is invalid");
        exit(1);
    }

    // Создаем векторых для хранения даных для всех доменов
    vectorVoid data = createVectorV(0, sizeof(DomainRecord));

    idxStart += sizeof(STATS_HEADER);
    idxEnd = idxEnd - sizeof(STATS_END) + 1;


    char *tokenStart = idxStart;
    int startToken = 0;
    while (idxStart <= idxEnd) {
        if (*idxStart != ' ') {
            startToken = 1;
        }

        if (*idxStart == ',') {
            // Парсим одну запись статистики
            parsedDomainStat(&data, tokenStart, idxStart - 1);
            startToken = 0;
        }

        idxStart++;

        if (!startToken) {
            tokenStart = idxStart;
        }
    }

    // Парсинг последнй записи статистики
    parsedDomainStat(&data, tokenStart, idxStart - 1);

    // Сортируем по названиям доменов
    qsort(data.data, data.size, sizeof(DomainRecord), compareDomainCounterNames);

    // Результатирующий вектор
    vectorVoid group = createVectorV(0, sizeof(DomainCounter));

    DomainRecord domain;
    DomainRecord prevDomain;
    getVectorValueV(&data, 0, &prevDomain);


    long totalSum = prevDomain.counter;
    for (int i = 1; i < data.size + 1; i++) {
        // Нахождение суммы у одинаковых элементов
        if (i != data.size) {
            getVectorValueV(&data, i, &domain);
            if (compareDomainCounterNames(&prevDomain, &domain) == 0) {
                totalSum += domain.counter;
                continue;
            }
        }

        // Заполнение структуры
        DomainCounter domainCounter = {totalSum};
        copy(prevDomain.domain.begin, prevDomain.domain.end, domainCounter.domain);
        pushBackV(&group, &domainCounter);

        prevDomain = domain;
        totalSum = prevDomain.counter;
    }

    // Очистка времменого вектора
    deleteVectorV(&data);

    return group;
}

int submatricesNum(int *matrix, int n, int m) {
    int (*tempMatrix)[m] = (int (*)[m]) matrix;

    for (int i = 0; i < n; i++) {
        int nums[m];
        for (int k = 0; k < m; k++) {
            nums[k] = 0;
        }
        for (int j = 0; j < m; j++) {
            if (tempMatrix[i][j] == 0) {
                nums[j] = 0;
            } else {
                if (j > 0) {
                    nums[j] = nums[j - 1] + 1;
                } else {
                    nums[j] += 1;
                }
            }
        }

        for (int k = 0; k < m; k++) {
            printf("%d\t", nums[k]);
        }
        printf("\n");
    }
}
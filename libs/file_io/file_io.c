#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"
#include "../string/tasks/string_.h"

char _fileReadBuffer[MAX_LINE_SIZE];

size_t readFileToBuff(char *filePath, char *buff, size_t buffSize) {
    FILE *f = fopen(filePath, "r");
    size_t size = fread(buff, sizeof(char), buffSize, f);
    fclose(f);
    buff[size] = '\0';

    return size;
}

//

size_t exponentialNumToNum(char *file_path_in, char *file_path_out) {
    FILE *fp = fopen(file_path_in, "r");
    FILE *fd = fopen(file_path_out, "w+");

    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }
    if (fd == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    size_t counter = 0;

    float val;
    while (fscanf(fp, "%e", &val) > 0) {
        fprintf(fd, "%.2f\n", val);
    }
    fclose(fp);
    fclose(fd);

    return counter;
}

int processOperation(int d1, int d2, char op) {
    switch (op) {
        case '+' :
            return d1 + d2;
            break;
        case '-' :
            return d1 - d2;
            break;
        case '/' :
            return d1 / d2;
            break;
        case '*' :
            return d1 * d2;
            break;
    }

    return 0;
}

size_t saveFileWithMathematicalExpression(char *file_path_in, char *file_path_out) {
    FILE *fp = fopen(file_path_in, "r");
    FILE *fd = fopen(file_path_out, "a+");

    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }
    if (fd == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    int countRes = 0;

    int d1, d2, d3;
    char op1, op2;
    int res;
    BagOfWords words;
    while (fgets(_fileReadBuffer, sizeof(_fileReadBuffer), fp) != NULL) {
        clearBagOfWords(&words);
        getBagOfWords(&words, _fileReadBuffer);

        if (words.size == 3) {
            d1 = *words.words[0].begin - '0';
            d2 = *words.words[2].begin - '0';
            op1 = *words.words[1].begin;
            res = processOperation(d1, d2, op1);
        } else if (words.size == 5) {
            d1 = *words.words[0].begin - '0';
            d2 = *words.words[2].begin - '0';
            d3 = *words.words[4].begin - '0';
            op1 = *words.words[1].begin;
            op2 = *words.words[3].begin;

            if (op1 == '*' || op1 == '/') {
                res = processOperation(d1, d2, op1);
                res = processOperation(res, d3, op2);
            } else {
                res = processOperation(d2, d3, op2);
                res = processOperation(d1, res, op1);
            }
        }

        countRes++;
        fprintf(fd,"%d\n", res);
    }

    fclose(fp);
    fclose(fd);

    return countRes;
}

int isPatternInWord(WordDescriptor word, const char *pattern) {
    int counter = 0;
    char *curPatternPtr = pattern;
    int len = strlen_(pattern);
    for (char *i = word.begin; i <= word.end; i += sizeof(char)) {
        if (*i == *curPatternPtr) {
            counter++;

            if (counter == len) {
                return 1;
            }
            curPatternPtr += sizeof(char);
        } else if (counter > 0) {
            counter = 0;
            curPatternPtr = pattern;
        }
    }
    return 0;
}

size_t saveFileWithRequiredLen(char *file_path_in, char *file_path_out, char *pattern) {
    FILE *fp = fopen(file_path_in, "r");
    FILE *fd = fopen(file_path_out, "w+");
    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }
    if (fd == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    size_t counter = 0;
    BagOfWords words;
    while (fgets(_fileReadBuffer, sizeof(_fileReadBuffer), fp) != NULL) {
        clearBagOfWords(&words);
        getBagOfWords(&words, _fileReadBuffer);

        for (int i = 0; i < words.size; i++) {
            WordDescriptor currWord = words.words[i];
            if (isPatternInWord(currWord, pattern)) {
                if (counter > 0) {
                    fputc(' ', fd);
                }
                fwrite(currWord.begin, currWord.end - currWord.begin, 1, fd);
                counter++;
            }
        }
    }
    fclose(fp);
    fclose(fd);

    return counter;
}

size_t saveFileWithLongestWord(char *file_path_in, char *file_path_out) {
    FILE *fp = fopen(file_path_in, "r");
    FILE *fd = fopen(file_path_out, "w+");
    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }
    if (fd == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    size_t counter = 0;
    BagOfWords words;
    while (fgets(_fileReadBuffer, sizeof(_fileReadBuffer), fp) != NULL) {
        clearBagOfWords(&words);
        getBagOfWords(&words, _fileReadBuffer);

        qsort(words.words, words.size, sizeof(WordDescriptor), compareWordDescriptorsByLen);

        WordDescriptor currWord = words.words[0];
        if (counter > 0) {
            fputc(' ', fd);
        }
        fwrite(currWord.begin, currWord.end - currWord.begin, 1, fd);
        counter++;
    }
    fclose(fp);
    fclose(fd);

    return counter;
}



#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"
#include "../string/tasks/string_.h"

char _fileReadBuffer[MAX_LINE_SIZE];

size_t readFileToBuff(char *filePath, char *buff, size_t buffSize) {
    FILE *f = fopen(filePath, "r");
    size_t size = fread(buff, sizeof(char), buffSize, f);
    fclose(f);

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

    size_t counter = 0;

    float val;
    while (fscanf(fp, "%e", &val) > 0) {
        fprintf(fd, "%.2f\n", val);
    }
    fclose(fp);
    fclose(fd);

    return counter;
}

//

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



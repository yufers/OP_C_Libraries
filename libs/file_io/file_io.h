#ifndef LAB_FILE_IO_H
#define LAB_FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024
extern char _fileReadBuffer[MAX_LINE_SIZE];

size_t readFileToBuff(char *filePath, char *buff, size_t buffSize);
size_t readFileBinaryToBuff(char *filePath, char *buff, size_t buffSize);

void rowsToColumnsInMatrix(char *filePath);

size_t exponentialNumToNum(char *filePath, char *fileOutputPath);

size_t saveFileWithMathematicalExpression(char *filePath, char *fileOutputPath);

size_t saveFileWithRequiredLen(char *filePath, char *fileOutputPath, char *pattern);

size_t saveFileWithLongestWord(char *filePath, char *fileOutputPath);

//

void binFileSort(char *filePath);

#endif //LAB_FILE_IO_H

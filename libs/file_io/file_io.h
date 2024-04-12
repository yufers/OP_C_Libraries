#ifndef LAB_FILE_IO_H
#define LAB_FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024
extern char _fileReadBuffer[MAX_LINE_SIZE];

size_t readFileToBuff(char *filePath, char *buff, size_t buffSize);

//

size_t exponentialNumToNum(char *s1, char *s2);

//

size_t saveFileWithRequiredLen(char *s1, char *s2, char *pattern);

size_t saveFileWithLongestWord(char *s1, char *s2);

#endif //LAB_FILE_IO_H

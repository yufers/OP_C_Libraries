#ifndef LAB_STRING__H
#define LAB_STRING__H

# include <stdint.h>

size_t strlen_(char *s);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char* findSpace(char *begin);

char* findNonSpaceReverse(char *rbegin, const char *rend);

char* findSpaceReverse(char *rbegin, const char *rend);

int strcmp_(const char *lhs, const char *rhs);

char* copy(const char *beginSource, const char *endSource, char *beginDestination);

int checkIfNotNum(int i);
char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));
char* copyIf2(char *beginSource, const char *endSource, char *beginDestination, int appendStringEnd, int (*f)(int));

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));

//---------------------------------------------------------------------------------------------------------------

#define MAX_STRING_SIZE 200

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

void removeNonLetters(char *s);

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line);

void removeAdjacentEqualLetters(char *s);

int getWord(char *beginSearch, WordDescriptor *word);
void digitInWordShift(WordDescriptor word);
void wordInStringProcessor(char *beginString, void(*f)(WordDescriptor));
void digitToStart(WordDescriptor word);

void digitInWordShift2(WordDescriptor word);
void wordInStringProcessor2(char *beginString, void(*f)(WordDescriptor));
void digitToStart2(WordDescriptor word);

void numToSpace(char *source);

int findWord(char *beginSearch, WordDescriptor *patternWord, WordDescriptor *resWord);
void replace(char *source, char *w1, char *w2);



#endif //LAB_STRING__H

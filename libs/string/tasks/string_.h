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
#define MAX_N_WORDS_IN_STRING 200

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;


void removeNonLetters(char *s);

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line);

void removeAdjacentEqualLetters(char *s);

int getWord(char *beginSearch, WordDescriptor *word);
void digitInWordShift(WordDescriptor word);
void wordInStringProcessor(char *beginString, void(*f)(WordDescriptor));
void digitToStart(WordDescriptor word);

///

void numToSpace(char *source);

int findWord(char *beginSearch, WordDescriptor *patternWord, WordDescriptor *resWord);
void replace(char *source, char *w1, char *w2);

int isOrdered(char *source);

void getBagOfWords(BagOfWords *bag, char *s);
void printBagOfWordsReverse(BagOfWords *bag);
void printWord(const WordDescriptor *word);
void clearBagOfWords(BagOfWords *bag);

int countPalindroms(char *s);

void getMixedString(char *res, char *s1, char *s2);

void stringReverse(char *s);

#endif //LAB_STRING__H

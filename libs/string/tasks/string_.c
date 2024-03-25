#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <memory.h>
#include "string_.h"

size_t strlen_(char *begin) {
    char *end = begin;
    while (*end != '\0')
        end += sizeof(char);
    return end - begin;
}

char* find(char *begin, char *end, int ch) {
    for (char *ptr = begin; ptr < end; ptr = ptr + sizeof(char)) {
        if (*ptr == ch) {
            return ptr;
        }
    }
    return end;
}

char* findNonSpace(char *begin) {
    char *ptr = begin;

    while (*ptr != '\0') {
        int res = 0;
        res = isspace(*ptr);
        if (!res) {
            return ptr;
        }

        ptr += sizeof(char);
    }
    return ptr;
}

char* findSpace(char *begin) {
    char *ptr = begin;

    while (*ptr != '\0') {
        int res = 0;
        res = isspace(*ptr);
        if (res) {
            return ptr;
        }

        ptr += sizeof(char);
    }
    return ptr;
}

char* findNonSpaceReverse(char *rbegin, const char *rend) {
    char *ptr = rbegin;
    bool found = false;

    while (ptr != rend) {
        int res = isspace(*ptr);

        if (!res) {
            found = true;
        } else {
            if (found) {
                return ptr + sizeof(char);
            }
        }

        ptr -= sizeof(char);
    }
    return rend;
}


//
char* findSpaceReverse(char *rbegin, const char *rend) {
    char *ptr = rbegin;
    bool found = false;

    while (ptr != rend) {
        int res = isspace(*ptr);

        if (!res) {
            found = true;
        } else {
            if (found) {
                return ptr;
            }
        }

        ptr -= sizeof(char);
    }
    return rend;
}

int strcmp_(const char *lhs, const char *rhs) {
    while (*lhs == *rhs++)
        if (*lhs++ == 0) return (0);
    return (*(unsigned char *) lhs - *(unsigned char *) --rhs);
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination) {
    size_t size = endSource - beginSource + 1;
    memcpy(beginDestination, beginSource, size);

    return beginDestination + size;
}

int checkIfNotNum(int i) {
    return i != ' ';
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    return copyIf2(beginSource, endSource, beginDestination, 1, f);
}

char* copyIf2(char *beginSource, const char *endSource, char *beginDestination, int appendStringEnd, int (*f)(int)) {
    for (char *i = beginSource; i <= endSource; i += sizeof(char)) {

    if (f(*i)) {
            *beginDestination = *i;
            beginDestination += sizeof(char);
        }
    }

    if (appendStringEnd) {
        *beginDestination = '\0';
    }

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    for (char *i = rbeginSource; i > rendSource; i -= sizeof(char)) {

        if (f(*i)) {
            *beginDestination = *i;
            beginDestination += sizeof(char);
        }
    }

    *beginDestination = '\0';
    return beginDestination;
}

//---------------------------------------------------------------------------------------------------------------

char _stringBuffer[MAX_STRING_SIZE + 1];

char* getEndOfString(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end += sizeof(char);
    return end - 1;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
}

void removeAdjacentEqualLetters(char *s) {
    char *endSource = getEndOfString(s);
    char prev = *s;
    char *dest = s;

    for (char *i = s + sizeof(char); i <= endSource; i += sizeof(char)) {
        if(*i != prev) {
            *dest = prev;
            dest += sizeof(char);
            prev = *i;
        }
    }

    *dest = *endSource;
    dest += sizeof(char);
    *dest = '\0';
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void digitInWordShift(WordDescriptor word) {
    digitToStart(word);
}

void wordInStringProcessor(char *beginString, void(*f)(WordDescriptor)) {
    char *beginSearch = beginString;
    WordDescriptor word;

    while (getWord(beginSearch, &word)) {
// обработка слова

        f(word);
        beginSearch = word.end;
    }
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf2(_stringBuffer, endStringBuffer, recPosition, 0, isalpha);
}

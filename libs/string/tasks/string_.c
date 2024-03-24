#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <memory.h>

size_t strlen_(const char *begin) {
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
    for (char *i = beginSource; i <= endSource; i += sizeof(char)) {

    if (f(*i)) {
            *beginDestination = *i;
            beginDestination += sizeof(char);
        }
    }

    *beginDestination = '\0';
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
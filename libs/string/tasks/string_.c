#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include "string_.h"


char _stringBuffer[MAX_STRING_SIZE + 1];
BagOfWords _bag;
BagOfWords _bag2;

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

char* findComma(char *begin) {
    char *ptr = begin;

    while (*ptr != '\0') {
        int res = 0;
        res = *ptr == ',';
        if (res) {
            return ptr;
        }

        ptr += sizeof(char);
    }
    return ptr;
}

char* findNonComma(char *begin) {
    char *ptr = begin;

    while (*ptr != '\0') {
        int res = 0;
        res = *ptr == ',';
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

char* findNonSpaceReverse(char *rbegin, char *rend) {
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
char* findSpaceReverse(char *rbegin, char *rend) {
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

char* getEndOfString(char *begin) {
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

int getWordReverse(char *beginSearch, char *endSearch, WordDescriptor *word) {
    word->begin = findNonSpaceReverse(beginSearch, endSearch);
    if (word->begin == beginSearch)
        return 0;
    word->end = beginSearch;
    return 1;
}

int getWordByComma(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonComma(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findComma(word->begin);
    return 1;
}

void digitInWordShift(WordDescriptor word) {
    digitToStart(word);
}

void digitInWordShift2(WordDescriptor word) {
    digitToEnd(word);
}

void wordInStringProcessor(char *beginString, void(*f)(WordDescriptor)) {
    char *beginSearch = beginString;
    WordDescriptor word;

    while (getWord(beginSearch, &word)) {
        f(word);
        beginSearch = word.end;
    }
}

void wordInStringProcessor2(char *beginString, void(*f)(WordDescriptor)) {
    char *beginSearch = beginString;
    WordDescriptor word;

    while (getWord(beginSearch, &word)) {
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

void digitToEnd(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf2(_stringBuffer, endStringBuffer, recPosition, 0, isalpha);
}

void numToSpace(char *source) {
    copy(source, getEndOfString(source), _stringBuffer);
    char *endSource = getEndOfString(_stringBuffer);
    char *recPtr = source;

    for (char *readPtr = _stringBuffer; readPtr <= endSource; readPtr += sizeof(char)) {
        if (isdigit(*readPtr)) {
            int num = *readPtr - '0' - 1;
            for (int j = 0; j <= num; j++) {
                *recPtr = ' ';
                recPtr += sizeof(char);
            }
        } else {
            *recPtr = *readPtr;
            recPtr += sizeof(char);
        }
    }

    recPtr += sizeof(char);
    *recPtr = '\0';
}

int findWord(char *beginSearch, WordDescriptor *patternWord, WordDescriptor *resWord) {
    int counter = 0;
    int wordLen = patternWord->end - patternWord->begin;
    char *searchPtr = patternWord->begin;;
    while (*beginSearch != '\0') {
        if (*beginSearch == *searchPtr) {
            counter++;
            searchPtr += sizeof(char);
        } else {
            counter = 0;
            searchPtr = patternWord->begin;
        }

        if (counter == wordLen) {
            resWord->begin = beginSearch - wordLen + 1;
            resWord->end = beginSearch + 1;
            return 1;
        }
        beginSearch += sizeof(char);
    }
    return 0;
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size * sizeof(char)};
    WordDescriptor word2 = {w2, w2 + w2Size * sizeof(char)};
    WordDescriptor wordRes;

    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (findWord(readPtr, &word1, &wordRes)) {
        if (readPtr != wordRes.begin) {
            recPtr = copy(readPtr, wordRes.begin - 1, recPtr);
        }
        recPtr = copy(word2.begin, word2.end - 1, recPtr);
        readPtr = wordRes.end;
    }

    char *readPtrEnd = getEndOfString(readPtr);
    if (readPtr >= readPtrEnd) {
        readPtr = copy(readPtr, readPtrEnd, recPtr);
    }
    *readPtr = '\0';
}

int isOrdered(char *source) {
    WordDescriptor wordRes;
    WordDescriptor prevWordRes;


    if (!getWord(source, &prevWordRes)) {
        return 1;
    }

    source = prevWordRes.end;
    while (getWord(source, &wordRes)) {


        unsigned long len1 = prevWordRes.end - prevWordRes.begin;
        unsigned long len2 = wordRes.end - wordRes.begin;
        unsigned long min_len = len1;
        if (min_len > len2) {
            min_len = len2;
        }

        int res = memcmp(prevWordRes.begin, wordRes.begin, min_len);

        if (res > 0) {
            return 0;
        }
        if (len1 > len2) {
            return 0;
        }

        prevWordRes = wordRes;
        source = wordRes.end;
    }
    return 1;
}

void getBagOfWords(BagOfWords *bag, char *s) {
    WordDescriptor wordRes;

    int i = 0;
    while (getWord(s, &wordRes)) {
        bag->words[i++] = wordRes;
        bag->size++;

        s = wordRes.end;
    }
}

void printBagOfWordsReverse(BagOfWords *bag) {
    for (int i = bag->size - 1; i >= 0; i--) {
        printWord(&bag->words[i]);
    }
}

void clearBagOfWords(BagOfWords *bag) {
    bag->size = 0;
}

void printWord(const WordDescriptor *word) {
    for (char *j = word->begin; j < word->end; j++) {
        printf("%c", *j);
    }
    printf("\n");
}

int isPalindrom(WordDescriptor *wordRes) {
    int is_polyndrom = 1;
    unsigned long len = (*wordRes).end - (*wordRes).begin;
    (*wordRes).end -= sizeof(char);

    for (int i = 0; i < len / 2; i++) {
        if (*(*wordRes).begin != *(*wordRes).end) {
            is_polyndrom = 0;
            break;
        }
        (*wordRes).begin += sizeof(char);
        (*wordRes).end -= sizeof(char);
    }
    return is_polyndrom;
}

int countPalindroms(char *s) {
    WordDescriptor wordRes;

    int counter = 0;

    while (getWordByComma(s, &wordRes)) {
        s = wordRes.end;
        counter += isPalindrom(&wordRes);
    }
    return counter;
}

void getMixedString(char *res, char *s1, char *s2) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {

        if (isW1Found) {
            if (*word1.end == '\0') {
                *word1.end = ' ';
            }

            copy(word1.begin, word1.end, res);
            res += word1.end - word1.begin + 1;
            beginSearch1 = word1.end;
        }
        if (isW2Found) {
            if (*word2.end == '\0') {
                *word2.end = ' ';
            }

            copy(word2.begin, word2.end, res);
            res += word2.end - word2.begin + 1;
            beginSearch2 = word2.end;
        }
    }
    *res = '\0';
}

void stringReverse(char *s) {
    copy(s, getEndOfString(s), _stringBuffer);

    WordDescriptor wordRes;
    char *end = getEndOfString(_stringBuffer) + sizeof(char);

    while ((end >= _stringBuffer) && getWordReverse(end, _stringBuffer,&wordRes)) {
        end = wordRes.begin - sizeof(char);

        copy(wordRes.begin, wordRes.end, s);
        s += wordRes.end - wordRes.begin;
        *s = ' ';
        s += sizeof(char);
    }
}

int hasWordLetter(WordDescriptor *word, char letter) {
    for (char *i = word->begin; i <= word->end; i += sizeof(char)) {
        if (*i == letter) {
            return 1;
        }
    }
    return 0;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *source, WordDescriptor *w) {
    WordDescriptor wordRes;
    WordDescriptor prevWordRes;


    if (!getWord(source, &prevWordRes)) {
        return EMPTY_STRING;
    }

    if (hasWordLetter(&prevWordRes, 'a') || hasWordLetter(&prevWordRes, 'A')) {
        w->begin = prevWordRes.begin;
        w->end = prevWordRes.end;
        return FIRST_WORD_WITH_A;
    }

    source = prevWordRes.end;
    while (getWord(source, &wordRes)) {

        if (hasWordLetter(&wordRes, 'a') || hasWordLetter(&wordRes, 'A')) {
            w->begin = prevWordRes.begin;
            w->end = prevWordRes.end;
            return WORD_FOUND;
        }

        prevWordRes = wordRes;
        source = wordRes.end;
    }
    return NOT_FOUND_A_WORD_WITH_A;
}

void printWordBeforeFirstWordWithA(char *s) {
    WordDescriptor word;
    WordBeforeFirstWordWithAReturnCode res = getWordBeforeFirstWordWithA(s, &word);

    switch (res) {
        case EMPTY_STRING:
            printf("В строке нет слов");
            break;
        case FIRST_WORD_WITH_A:
            printf("Первое слово с ’a’ является первым в строке\n");
            printWord(&word);
            break;
        case WORD_FOUND:
            printf("Имеется слово перед словом с ’a’\n");
            printWord(&word);
        case NOT_FOUND_A_WORD_WITH_A:
            printf("В строке нет слов с ’a’");
            break;
    }
}

void assertString(const char *expected, char *got,char const *fileName, char const *funcName, int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else {
        fprintf(stderr, "%s - OK\n", funcName);
    }
}

void findLastWord(char *s1, char *s2) {
    clearBagOfWords(&_bag);
    clearBagOfWords(&_bag2);
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    size_t len1 = 0;
    size_t len2 = 0;

    for (int i = _bag.size - 1; i >= 0; i--) {
        for (int j = _bag2.size - 1; j >= 0; j--) {
            len1 = &_bag.words[i].end - &_bag.words[i].begin;
            len2 = &_bag2.words[j].end - &_bag2.words[j].begin;

            if (len1 != len2) {
                continue;
            }

            int res = memcmp(_bag.words[i].begin, _bag2.words[j].begin, len1);

            if (res == 0) {
                printWord(&_bag.words[i]);
            }
        }
    }
}

int compareWordDescriptors(const void *wordPtr1, const void *wordPtr2) {
    WordDescriptor *word1 = (WordDescriptor *)wordPtr1;
    WordDescriptor *word2 = (WordDescriptor *)wordPtr2;

    unsigned long len1 = word1->end - word1->begin;
    unsigned long len2 = word2->end - word2->begin;
    unsigned long min_len = len1;
    if (min_len > len2) {
        min_len = len2;
    }

    int res = memcmp(word1->begin, word2->begin, min_len);

    if (res == 0) {
        if (len1 != len2) {
            res = len1 > len2 ? 1 : -1;
        }
    }
    return res;
}


int hasSameWords(char *s) {
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, s);
    qsort(_bag.words, _bag.size, sizeof(WordDescriptor), compareWordDescriptors);

    for (int i = 1; i <= _bag.size; i++) {
        int res = compareWordDescriptors(&_bag.words[i - 1], &_bag.words[i]);

        if (res == 0) {
            return 1;
        }
    }
    return 0;
}

int compareLetters(const void* charPtr1, const void* charPtr2) {
    const char *char1 = (const char*)charPtr1;
    const char *char2 = (const char*)charPtr2;

    return *char1 - *char2;
}

int hasWordsWithSameLetters(char *s) {
    copy(s, getEndOfString(s), _stringBuffer);
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, _stringBuffer);

    for (int i = 0; i <= _bag.size; i++) {
        qsort(_bag.words[i].begin, _bag.words[i].end - _bag.words[i].begin, sizeof(char), compareLetters);
    }

    qsort(_bag.words, _bag.size, sizeof(WordDescriptor), compareWordDescriptors);

    for (int i = 1; i <= _bag.size; i++) {
        int res = compareWordDescriptors(&_bag.words[i - 1], &_bag.words[i]);

        if (res == 0) {
            return 1;
        }
    }
    return 0;
}

void getStringWithoutEndWords(char *s) {
    copy(s, getEndOfString(s), _stringBuffer);
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, _stringBuffer);
    WordDescriptor lastWord = _bag.words[_bag.size - 1];

    for (int i = 0; i < _bag.size - 1; i++) {
        WordDescriptor currWord = _bag.words[i];
        int res = compareWordDescriptors(&currWord, &lastWord);
        
        if (res != 0) {
            copy(currWord.begin, currWord.end, s);
            s += currWord.end - currWord.begin;
            *s = ' ';
            s += sizeof(char);
        }
    }
    *s = '\0';
}

int findWordBefore(char *s1, char *s2, char *res) {
    clearBagOfWords(&_bag);
    clearBagOfWords(&_bag2);
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    int get;
    for (int i = 1; i < _bag.size - 1; i++) {
        WordDescriptor lineOneWord = _bag.words[i];
        for (int j = 0; j < _bag2.size - 1; j++) {
            WordDescriptor lineTwoWord = _bag2.words[j];
            get = compareWordDescriptors(&lineOneWord, &lineTwoWord);
            
            if (get == 0) {
                WordDescriptor resWord = _bag.words[i - 1];
                copy(resWord.begin, resWord.end, res);
                res += resWord.end - resWord.begin;
                *res = '\0';
                return 1;
            }
        }
    }
    return 0;
}

void deletePalindromes(char *s) {
    copy(s, getEndOfString(s), _stringBuffer);
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, _stringBuffer);

    for (int i = 0; i < _bag.size; i++) {
        WordDescriptor lineOneWord = _bag.words[i];

        int isPal = isPalindrom(&lineOneWord);

        if (!isPal) {
            copy(lineOneWord.begin, lineOneWord.end, s);
            s += lineOneWord.end - lineOneWord.begin + 1;
            *s = ' ';
            s += sizeof(char);
        }
    }
    *s = '\0';
}
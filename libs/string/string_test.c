#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tasks/string_.h"
#include "string_test.h"

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

void testAll_removeNonLetters() {
    char s1[] = "abc dtr yu\0";
    removeNonLetters(s1);
    ASSERT_STRING("abcdtryu", s1);
}

void testAll_removeAdjacentEqualLetters() {
    char s1[] = "abcc aaabbbtr yuu\0";
    removeAdjacentEqualLetters(s1);
    ASSERT_STRING("abc abtr yu", s1);
}

void testAll_numToSpace() {
    char s1[] = "a1rt3b\0";
    numToSpace(s1);
    ASSERT_STRING("a rt   b", s1);
}

void testAll_replace() {
    char s[MAX_STRING_SIZE] = "butterfly three butterfly\0";
    char s1[] = "butterfly\0";
    char s2[] = "dog\0";
    replace(s, s1, s2);
    ASSERT_STRING("dog three dog", s);
}

void testAll_isOrdered() {
    char s1[] = "abc defg hx\0";
    int res = isOrdered(s1);
    assert(res == 1);
}

void testAll_countPalindroms() {
    char s1[] = "aba,asdf,zxxz,huji,abcdcba\0";
    int res = countPalindroms(s1);
    assert(res == 3);
}

void testAll_getMixedString() {
    char s[MAX_STRING_SIZE] = "";
    char s1[] = "aga1 buga3 duga5 kol6 ola7\0";
    char s2[] = "rug2 tot4\0";
    getMixedString(s, s1, s2);
    ASSERT_STRING("aga1 rug2 buga3 tot4 duga5 kol6 ola7", s);
}

void testAll_stringReverse() {
    char s1[] = "dog tot three\0";
    stringReverse(s1);
    ASSERT_STRING("three tot dog", s1);
}

void testAll_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(
            getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING
    );
    char s2[] = "ABC";
    assert(
            getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A
    );
    char s3[] = "BC A";
    assert(
            getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND
    );
    char got[MAX_STRING_SIZE];
    copy(word.begin, word.end, got);
    got[word.end - word.begin] = '\0';
    ASSERT_STRING("BC", got);
    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void testAll_hasSameWords() {
    char s1[] = "ada tot three ada hox\0";
    int res = hasSameWords(s1);
    assert(res == 1);
}

void testAll_hasWordsWithSameLetters() {
    char s1[] = "anton bot bkf len anton\0";
    int res = hasWordsWithSameLetters(s1);
    assert(res == 1);
}

void testAll_getStringWithoutEndWords() {
    char s1[] = "anton bot bkf len anton\0";
    getStringWithoutEndWords(s1);
    ASSERT_STRING("bot bkf len", s1);
}

void testAll_findWordBefore() {
    char s1[MAX_STRING_SIZE] = "bot anton len size\0";
    char s2[MAX_STRING_SIZE] = "word get anton dot\0";
    char res[MAX_STRING_SIZE];
    int found = findWordBefore(s1, s2, res);
    assert(found == 1);
}

void testAll_deletePalindromes() {
    char s1[] = "ava bot bkf len acdca\0";
    deletePalindromes(s1);
    ASSERT_STRING("bot bkf len", s1);
}

void testAll_appendMissingWords() {
    char s1[MAX_STRING_SIZE] = "anton bot\0";
    char s2[MAX_STRING_SIZE] = "get size let dot got\0";
    appendMissingWords(s1, s2);
    ASSERT_STRING("anton bot let dot got", s1);
}

void testAll_isStringIncludeLetters() {
    char s1[MAX_STRING_SIZE] = "anton bot z\0";
    char s2[MAX_STRING_SIZE] = "otaz\0";
    int found = isStringIncludeLetters(s1, s2);
    assert(found == 1);
}

void testStringAll() {
    testAll_removeNonLetters();
    testAll_removeAdjacentEqualLetters();
    testAll_numToSpace();
    testAll_replace();
    testAll_isOrdered();
    testAll_countPalindroms();
    testAll_getMixedString();
    testAll_stringReverse();
    testAll_getWordBeforeFirstWordWithA();
    testAll_hasSameWords();
    testAll_hasWordsWithSameLetters();
    testAll_getStringWithoutEndWords();
    testAll_findWordBefore();
    testAll_deletePalindromes();
    testAll_appendMissingWords();
    testAll_isStringIncludeLetters();
}
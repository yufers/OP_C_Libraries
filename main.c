#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/string/tasks/string_.h"

//size_t test_strlen_() {
//    char *s = "abcdefg";
//
//    size_t res = strlen_(s);
//    assert(res == 7);
//}
//
//char* test_find() {
//    char *s = "Hello";
//
//    char *res = find(&s[0], &s[3], 'e');
//    assert(*res == 'e');
//}
//
//char* test_findNonSpace() {
//    char *s = "   d  ";
//
//    char *res = findNonSpace(s);
//    assert(*res == 'd');
//}
//
//char* test_findSpace() {
//    char *s = "rew hj";
//
//    char *res = findSpace(s);
//    assert(*res == ' ');
//}
//
//char* test_findNonSpaceReverse() {
//    char *s = "test test ";
//
//    char *res = findNonSpaceReverse(s + sizeof(char) * 9, s);
//    assert(*res == 't');
//}
//
//char* test_findSpaceReverse() {
//    char *s = "ab de";
//
//    char *res = findSpaceReverse(s + sizeof(char) * 5, s);
//    assert(*res == ' ');
//}
//
//int test_strcmp_() {
//    char *lhs1 = "ABCD";
//    char *rhs1 = "EFGH";
//    int res1 = strcmp_(lhs1, rhs1);
//    assert(res1 < 0);
//
//    char *lhs2 = "ABCD";
//    char *rhs2 = "ABCD";
//    int res2 = strcmp_(lhs2, rhs2);
//    assert(res2 == 0);
//
//    char *lhs3 = "ZXCV";
//    char *rhs3 = "BHFR";
//    int res3 = strcmp_(lhs3, rhs3);
//    assert(res3 > 0);
//}
//
//char* test_copy() {
//    char *s = "12345333333333333333";
//    char sd[20] = {1,1,1,1,1,1,1,1,1,1,1,1,1};
//
//    char *res = copy(s, s + sizeof(char) * 4, sd);
//    assert(*res == 1);
//}
//
//char* test_copyIf() {
//    char *s = "123456";
//    char sd[20] = {1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,};
//
//    char *res = copyIf(s, s + sizeof(char) * 5, sd, &checkIfNotNum);
//    assert(res[0] == 0 && res[1] == 1);
//}
//
//char* test_copyIfReverse() {
//    char *s = "123456";
//    char sd[20] = {1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,};
//
//    char *res = copyIfReverse(s + sizeof(char) * 5, s, sd, &checkIfNotNum);
//    assert(res[0] == 0 && res[1] == 1);
//}
//
//void test() {
//    test_strlen_();
//    test_find();
//    test_findNonSpace();
//    test_findSpace();
//    test_findNonSpaceReverse();
//    test_findSpaceReverse();
//    test_strcmp_();
//    test_copy();
//    test_copyIf();
//    test_copyIfReverse();
//}

int main() {
//    test();

    char s[] = "abc def gd\0";
    removeNonLetters(s);
    printf("%s", s);

    return 0;
}

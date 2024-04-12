#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "file_io.h"
#include "file_io_test.h"
#include "../string/string_test.h"
#include "../string/tasks/string_.h"

char testBuff[MAX_LINE_SIZE];

FILE testAll_saveFileWithRequiredLen() {
    FILE *fp = fopen ("file_test1.txt", "w+");
    char word[4] = "bot";

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fputs("bot vdg uy\n", fp);
        } else if (i % 3 == 0) {
            fputs("rama ho isz\n", fp);
        } else {
            fputs("1z i7 bj\n", fp);
        }
    }
    fclose(fp);

    size_t res = saveFileWithRequiredLen("file_test1.txt", "file_test2.txt", word);
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 5);
    assert(fileSize == 19);
    ASSERT_STRING("bot bot bot bot bot", testBuff)
}

FILE testAll_saveFileWithLongestWord() {
    FILE *fp = fopen ("file_test1.txt", "w+");

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fputs("anton hg jui\n", fp);
        } else if (i % 3 == 0) {
            fputs("bhy gamma po\n", fp);
        } else {
            fputs("dd ll rock\n", fp);
        }
    }
    fclose(fp);

    size_t res = saveFileWithLongestWord("file_test1.txt", "file_test2.txt");
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 10);
    assert(fileSize == 56);
    ASSERT_STRING("anton rock anton gamma anton rock anton rock anton gamma", testBuff)
}

void testFileAll() {
    testAll_saveFileWithRequiredLen();
    testAll_saveFileWithLongestWord();
}
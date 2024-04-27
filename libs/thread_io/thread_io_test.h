#ifndef LAB_THREAD_IO_TEST_H
#define LAB_THREAD_IO_TEST_H

#include <stdio.h>
#include <stdlib.h>

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__);

void testThreadAll();

#endif //LAB_THREAD_IO_TEST_H

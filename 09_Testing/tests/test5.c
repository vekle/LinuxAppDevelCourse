#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

#include "buf.h"

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x) \
    do { \
        if (x) { \
            printf(C_GREEN("PASS") " %s\n", s); \
            count_pass++; \
        } else { \
            printf(C_RED("FAIL") " %s\n", s); \
            count_fail++; \
        } \
    } while (0)

int
main(int argc, char **argv)
{
    /* volatile due to setjmp() / longjmp() */
    volatile int count_pass = 0;
    volatile int count_fail = 0;

    /* buf_pop() */
    int *a = 0;
    buf_push(a, 1);
    buf_push(a, 2);
    buf_push(a, 3);
    buf_push(a, 4);
    TEST("size 4", buf_size(a) == 4);
    TEST("pop 3", buf_pop(a) == 4);
    buf_trunc(a, 3);
    TEST("size 3", buf_size(a) == 3);
    TEST("pop 2", buf_pop(a) == 3);
    TEST("pop 1", buf_pop(a) == 2);
    TEST("pop 0", buf_pop(a) == 1);
    TEST("size 0 (pop)", buf_size(a) == 0);
    buf_free(a);

    printf("%d fail, %d pass\n", count_fail, count_pass);
    return count_fail != 0;
}
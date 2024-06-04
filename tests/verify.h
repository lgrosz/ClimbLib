#ifndef _CLIMBLIB_TESTS_VERIFY_H_
#define _CLIMBLIB_TESTS_VERIFY_H_

#include <stdio.h>

#define VERIFY(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Verification failed at %s:%d - %s\n", __FILE__, __LINE__, #expr); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#endif

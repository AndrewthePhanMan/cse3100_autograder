#ifndef TEST_H
#define TEST_H

#include "parser.h"

typedef struct {
    char output[4096];
    int passed;
    int score;
    int timed_out;
    int crashed;
    int exit_status;
} Result;

Result run_test(Test *test);

#endif
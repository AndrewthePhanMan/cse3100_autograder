#ifndef RUNNER_H
#define RUNNER_H

#include "test.h"

typedef struct {
    char output[4096];
    int exit_status;
    int timed_out;
    int crashed;
} RunData;

void build_cmd(char *dest, Test *t);
RunData run(char *cmd, char *input);

#endif
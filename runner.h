#ifndef RUNNER_H
#define RUNNER_H

void build_cmd(char *dest, Test *t);
int run(char *cmd, char *input, char *output);

#endif
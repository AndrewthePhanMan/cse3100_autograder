#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char name[256];
    char cmd[256];
    char args[1024];
    char input[1024];
    char expected_output[1024];
    int score;
} Test;

void print_test(Test *test);
void extract(char *line, char *field);
int parse(char *tests_file, Test tests[]);

#endif
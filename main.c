#include <stdio.h>
#include "parser.h"
#include "test.h"
#include "output.h"

int main(int argc, char *argv[])
{
    char *submission = argv[1];
    char *test_file = argv[2];

    Test tests[100];
    Result results[100];

    int count = parse(test_file, tests);

    for (int i = 0; i < count; i++)
        results[i] = run_test(&tests[i]);

    write_results("results.json", tests, results, count);

    return 0;
}
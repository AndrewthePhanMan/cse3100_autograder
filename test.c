#include <string.h>
#include "test.h"
#include "runner.h"

Result run_test(Test *test)
{
    Result result;
    memset(&result, 0, sizeof(Result));

    char output[4096];
    memset(output, 0, sizeof(output));

    char *input = NULL;
    if (strcmp(test->input, "NONE") != 0)
        input = test->input;
    
    char cmd[256];
    build_cmd(cmd, test);
    run(cmd, input, output);

    strcpy(result.output, output);

    if (strcmp(test->expected_output, "NONE") == 0)
        result.passed = 1;
    else
        result.passed = (strcmp(output, test->expected_output) == 0);
    
    if (result.passed)
        result.score = test->score;
    else
        result.score = 0;

    return result;
}
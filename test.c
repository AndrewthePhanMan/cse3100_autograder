#include <string.h>
#include "test.h"
#include "runner.h"

Result run_test(Test *test)
{
    Result result;
    memset(&result, 0, sizeof(Result));

    char *input = NULL;
    if (strcmp(test->input, "NONE") != 0)
        input = test->input;
    
    char cmd[256];
    build_cmd(cmd, test);

    RunData run_data = run(cmd, input);

    strcpy(result.output, run_data.output);

    result.timed_out = run_data.timed_out;
    result.crashed = run_data.crashed;
    result.exit_status = run_data.exit_status;

    if (result.exit_status != 0)
    {
        result.passed = 0;
        result.score = 0;
        return result;
    }

    if (result.timed_out || result.crashed)
    {
        result.passed = 0;
        result.score = 0;
        return result;
    }

    if (strcmp(test->expected_output, "NONE") == 0)
        result.passed = 1;
    else
        result.passed = (strcmp(result.output, test->expected_output) == 0);
    
    if (result.passed)
        result.score = test->score;
    else
        result.score = 0;

    return result;
}
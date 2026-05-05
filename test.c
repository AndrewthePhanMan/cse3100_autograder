#include <string.h>
#include "test.h"
#include "runner.h"

Result run_test_case(Test *test)
{
    Result result;
    memset(&result, 0, sizeof(Result));

    char output[4096];
    memset(output, 0, sizeof(output));

    run(test->cmd, test->input, output);

    strcpy(result.output, output);

    result.passed = (strcmp(output, test->expected_output) == 0);

    return result;
}
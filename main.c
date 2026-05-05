#include <stdio.h>
#include "parser.h"
#include "runner.h"

int main()
{
    Test tests[100];

    int count = parse("tests.txt", tests);

    for (int i = 0; i < count; i++)
    {
        print_test(&tests[i]);
        printf("\n");
    }
}
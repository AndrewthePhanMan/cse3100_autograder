#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

void print_test(Test *test)
{
    printf("Test: %s\n", test->name);
    printf("Cmd: %s\n", test->cmd);
    printf("Input: %s\n", test->input);
    printf("Expected Output: %s\n", test->expected_output);
    printf("Score: %d\n", test->score);
}

void unescape(char *str)
{
    char buffer[1024];
    int i = 0;
    int j = 0;

    while (str[i])
    {
        if (str[i] == '\\' && str[i + 1] == 'n')
        {
            buffer[j++] = '\n';
            i += 2;
        }
        else
            buffer[j++] = str[i++];
    }

    buffer[j] = '\0';
    strcpy(str, buffer);
}

void extract(char *line, char *field)
{
    char *first_quote = strchr(line, '"');
    if (!first_quote)
        return;

    char *second_quote = strchr(first_quote + 1, '"');
    if (!second_quote)
        return;
    
    char *value_start = strchr(second_quote + 1, '"');
    if (!value_start)
        return;
    
    value_start++;

    char *value_end = strchr(value_start, '"');
    if (!value_end)
        return;

    int len = value_end - value_start;
    strncpy(field, value_start, len);
    field[len] = '\0';
    unescape(field);
}

int parse(char *tests_file, Test tests[])
{
    FILE *file = fopen(tests_file, "r");

    char line[1024];
    int status = 0;
    int count = 0;
    Test test;
    
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "test_"))
        {
            memset(&test, 0, sizeof(Test));
            status = 1;
        }
        
        else if (strstr(line, "end"))
        {
            tests[count++] = test;
            status = 0;
        }

        else if (status)
        {
            if (strstr(line, "\"name\""))
                extract(line, test.name);
            
            else if (strstr(line, "\"program\""))
                extract(line, test.program);
            
            else if (strstr(line, "\"cmd\""))
                extract(line, test.cmd);
            
            else if (strstr(line, "\"input\""))
                extract(line, test.input);
            
            else if (strstr(line, "\"expected_output\""))
                extract(line, test.expected_output);
            
            else if (strstr(line, "\"score\""))
                sscanf(line, " \"score\": %d", &test.score);
        }
    }

    fclose(file);
    return count;
}
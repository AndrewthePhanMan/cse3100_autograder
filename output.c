#include <stdio.h>
#include "output.h"

void escape(char *new_output, char *output)
{
    int i = 0;
    int j = 0;

    while (output[i])
    {
        if (output[i] == '\n')
        {
            new_output[j++] = '\\';
            new_output[j++] = 'n';
        }
        else if (output[i] == '"')
        {
            new_output[j++] = '\\';
            new_output[j++] = '"';
        }
        else
            new_output[j++] = output[i];

        i++;
    }

    new_output[j] = '\0';
}

void write_results(const char *filename, Test tests[], Result results[], int count)
{
    FILE *results_file = fopen(filename, "w");

    fprintf(results_file, "{\n    \"tests\": [\n");

    for (int i = 0; i < count; i++)
    {
        Result result = results[i];

        fprintf(results_file, "  {\n");
        fprintf(results_file, "      \"name\": \"%s\",\n", tests[i].name);
        fprintf(results_file, "      \"passed\": %s,\n", result.passed ? "true" : "false");

        char new_output[4096];
        escape(new_output, result.output);
        fprintf(results_file, "      \"output\": \"%s\",\n", new_output);

        fprintf(results_file, "      \"score\": %d\n", result.score);
        fprintf(results_file, "  }%s\n", (i < count - 1) ? "," : "");
    }

    fprintf(results_file, " ]\n}\n");

    fclose(results_file);
}
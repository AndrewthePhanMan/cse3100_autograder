#ifndef OUTPUT_H
#define OUTPUT_H

#include "test.h"

void escape(char *new_output, char *output);
void write_results(const char *filename, Test tests[], Result results[], int count);

#endif
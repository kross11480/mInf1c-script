#pragma once
#include <stddef.h>
#define MAX_LINE_LEN 80
#define MAX_TOKENS 3

void shell_readline(char buf[], size_t bufsize);
int shell_evaluate(const char *line);
void shell_init();
void shell_run();

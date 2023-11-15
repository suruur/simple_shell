#ifndef MY_H
#define MY_H
#include <unistd.h>

extern char **environ;

void execute_command(char *args[], char *fn);

void print_env(void);

void parse_input(char *input, char *fn);

#endif

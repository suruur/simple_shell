#ifndef MY_H
#define MY_H

extern char **environ;

void execute_command(char *args[], char *fn);

void parse_input(char *input, char *fn);

#endif

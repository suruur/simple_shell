#ifndef MY_H
#define MY_H

extern char **environ;

void execute_command(char *args[], char *fn);

void parse_input(char *input, char *fn);

int _myexit(info_t *info)

int _mycd(info_t *info)

int _myhelp(info_t *info)

#endif

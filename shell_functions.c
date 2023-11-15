#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shell_x.h"

/**
 * execute_command - run command
 * @args: array of command
 * @fn: file name
 *
 * Return: void
 */
void execute_command(char *args[], char *fn)
{
	pid_t pid;

	pid = fork();

	if (pid == 0)
	{
		/* Child process */
		execve(args[0], args, environ);
		perror(fn);
	}
	else
	{
		if (pid < 0)
		{
			perror("fork()");
		}
		else
		{
			/* Parent Process */

			waitpid(pid, NULL, 0);
		}
	}
}

/**
 * parse_input - handle input
 * @input: command
 * @fn: file name
 *
 * Return: void
 */
void parse_input(char *input, char *fn)
{
	char *args[64];
	int i;
	char *token;

	i = 0;
	token = strtok(input, " \t\n");

	while (token != NULL && i < 63)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (i > 0)
	{
		if (strcmp(args[0], "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute_command(args, fn);
		}
	}
}

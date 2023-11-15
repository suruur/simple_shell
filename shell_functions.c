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
	char *path_env, *path_c, *path_t;
	char cmd_path[1024];
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		/* Child process */
		path_env = getenv("PATH");
		path_c = strdup(path_env);
		path_t = strtok(path_c, ":");

		while (path_t != NULL)
		{
			snprintf(cmd_path, sizeof(cmd_path), "%s/%s", path_t, args[0]);
			if (access(cmd_path, X_OK) == 0)
			{
				execve(cmd_path, args, environ);
			}
			path_t = strtok(NULL, ":");
		}
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

			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
}
/**
 * print_env - print env var
 * Return: void
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
/**
 * exit_shell - exit shell
 * @args: args
 * Return: void
 */
void exit_shell(char **args)
{
	int st = 0;

	if (args[1] != NULL)
	{
		st = atoi(args[1]);
	}

	exit(st);
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
			/* printf("Exiting..\n"); */
			exit_shell(args);
		}
		else
		{
			execute_command(args, fn);
		}
	}
}

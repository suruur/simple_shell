#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt()
{
	printf("#simple_shell$ ");
       	fflush(stdout);
}
int read_command(char *buffer)
{
       	if (fgets(buffer, MAX_INPUT_SIZE, stdin) == NULL)
       	{
	       	if (feof(stdin))
	       	{
		       	return 0;
	       	}
	       	else
	       	{
			perror("Error Promting");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

void execute_command(char *command)
{
       	size_t length = strlen(command);

	if (length > 0 && command[length - 1] == '\n')
	{
		command[length - 1] = '\0';	
	}

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork(): failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (pid == 0)
		{
			char *args[2];
			args[0] = command;
			args[1] = NULL;

			if (execve(command, args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid: failed");
				exit(EXIT_FAILURE);
			}
		}
	}

}
int main()
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		display_prompt();
		
		if (!read_command(input))
		{
			break;
		}

		execute_command(input);
	}
	printf("\n");
	return (0);
}

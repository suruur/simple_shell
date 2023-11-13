#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;

void displayPrompt()
{
       	printf("($) ");
}
int main(int arc, char *argv[])
{
	int status;
	pid_t pid;
	char *args[64];
	int argc;
	char *str, *arv;
	char input[1024];


	argc = 0;

	if (arc > 0)
		arv = argv[0];

	while (1)
	{
		displayPrompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n"); 
			break;
		}
		
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			printf("Exiting...\n");
			break;
		}

		if (strlen(input) > 0)
		{
			pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (pid == 0)
			{
				str = strtok(input, " ");
				while (str != NULL)
				{
					args[argc++] = str;
					str = strtok(NULL, " ");
				}
				args[argc] = NULL;

				if (execve(args[0], args, environ) == -1)
				{
					perror(arv);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				/* Parent Process */
				waitpid(pid, &status, 0);

			}
		}
		}
	}

	return (0);
}

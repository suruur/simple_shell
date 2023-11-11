#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_INPUT_SIZE 1024

void displayPrompt()
{
       	printf("#simple_shell$ ");
}
int main(int arc, char *argv[])
{
	int status;
	pid_t pid;
	char *args[64];
	int argc;
	char *str, *arv;

	argc = 0;
	
	char input[MAX_INPUT_SIZE];

	/*
	if (arc > 0)
	printf("-----%s\n", argv[0]);
	*/
	arv = argv[0];

	while (1)
	{
		displayPrompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n Exiting simple_shell...\n");
			break;
		}
		
		input[strcspn(input, "\n")] = '\0';

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

				if (strcmp(input, "exit") == 0)
				{
					printf("exit -------\n");
					break;
				}
				else
				{
					if (execve(args[0], args, NULL) == -1)
					{
						perror(arv);
						exit(EXIT_FAILURE);
					}
				}
			}
			else
			{
				/* Parent Process */
				waitpid(pid, &status, 0);

			}
		}
	}

	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 100

int main()
{
	int status;
	char input[MAX_INPUT_SIZE];
	size_t in_len;

	while (1)
	{
		printf("simple_shell> ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n Exiting simple_shell...\n");
			break;
		}
		in_len = strlen(input);

		if (in_len > 0 && input[in_len - 1] == '\n')
		{
			input[in_len - 1] = '\0';
		}
		if (strlen(input) > 0)
		{
			pid_t child_pid = fork();

			if (child_pid == -1)
			{
				perror("fork");
			}
			else
				if (child_pid == 0)
				{
					execlp(input, input, (char *)NULL);

					perror("exec");
					exit(EXIT_FAILURE);
				}
				else
				{
					waitpid(child_pid, &status, 0);
					
					if (WIFEXITED(status))
					{
						printf("Child process exited with status %d\n", WEXITSTATUS(status));
					}
					else
						if (WIFSIGNALED(status))
						{
							printf("Child process terminated by signal %d\n", WTERMSIG(status));
						}
				}


		}

	}

	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell_x.h"

/**
 * main - Entry point
 * @argc: args count
 * @argv: args values
 * Return: Always 0 Success
 */

int main(int argc, char *argv[])
{
	char input[64];
	char *fn;

	fn = argv[0];

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			printf("($) ");

			if (fgets(input, sizeof(input), stdin) == NULL)
			{
				printf("\n");
				break;
			}
			input[strcspn(input, "\n")] = '\0';
			parse_input(input, fn);
		}
	}
	else
	{
		if (argc != 1)
		{
			fprintf(stderr, "Usage: %s/n", argv[0]);
			exit(EXIT_FAILURE);
		}

		while (fgets(input, sizeof(input), stdin) != NULL)
		{
			parse_input(input, fn);
		}
	}

	return (EXIT_SUCCESS);
}

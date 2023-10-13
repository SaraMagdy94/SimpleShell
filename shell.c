#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 *  * execute - A function that executes a command.
 *   * @c: A pointer to a string containing the command to be executed.
 *    */

void execute(char *c)
{
	pid_t p = fork();

	if (p == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (p == 0)
	{
		char *args[2];
		args[0] = c;
		args[1] = NULL;
		execvp(c, args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		int s;
		wait(&s);
	}
}

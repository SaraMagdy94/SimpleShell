#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * token - A function that executes a command.
 * execute - A function that executes a command.
 * @r: A pointer to a string containing the command to be executed.
 * @a: A pointer to a string containing the command to be executed.

*/
void token(char *r, char *a[])
{
int i = 0;
char *t = r;

while (*t != '\0' && i < BUFFER_SIZE)
{
while (*t == ' ' || *t == '\t' || *t == '\n')
*t++ = '\0';

a[i++] = t;

while (*t != '\0' && *t != ' ' && *t != '\t' && *t != '\n')
t++;
}
a[i] = NULL;
}


void execute(char *a[])
{
pid_t p = fork();

if (p == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (p == 0)
{
execvp(a[0], a);
perror("execvp");
exit(EXIT_FAILURE);
}
else
{
int s;
wait(&s);
}
}

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024
static char buffer[BUFFER_SIZE];
static size_t p;
/**
 * _getline - Custom implementation of getline function
 * Return: A pointer to the string read, or NULL on failure or end of input
 */
char *_getline(void)
{
char *l = NULL;
size_t bufsize = 0;
ssize_t r;
char *n;
while (1)
{
if (p == 0)
{
r = read(STDIN_FILENO, buffer, BUFFER_SIZE);
if (r == -1 || r == 0)
{
return (NULL);
}
buffer[r] = '\0';
}
n = strchr(buffer + p, '\n');
if (n != NULL)
{
*n = '\0';
bufsize = n - buffer + 1;
l = malloc(bufsize);
if (l == NULL)
return (NULL);
strcpy(l, buffer);
p = n - buffer + 1;
break;
}
else
{
bufsize += strlen(buffer + p) + 1;
l = realloc(l, bufsize);
if (l == NULL)
return (NULL);
strcat(l, buffer + p);
p = 0;
}
}
return (l);
}

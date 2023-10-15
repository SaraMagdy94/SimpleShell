#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <unistd.h>
#include <string.h>

/**
 * main - Entry point of the program.
 *
 * This function continuously reads input from the user,
 * processes it using the custom _getline function,
 *  and prints the received input to the standard output.
 * If an error occurs during input reading,
 * it prints an error message and exits.
 *
 * Return: Always returns 0 to indicate successful execution.
 */

int main(void)
{
char *line;

while (1)
{
line = _getline();

if (line == NULL)
{
perror("Error reading input");
break;
}
else if (line[0] == '\0')
{
free(line);
break;
}
else
{
write(STDOUT_FILENO, "The input Is: ", 13);
write(STDOUT_FILENO, line, strlen(line));
write(STDOUT_FILENO, "\n", 1);
free(line);
}
}

return (0);
}

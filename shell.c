#include "main.h"
/**
 * token - Tokenize a string into an array of arguments.
 * @r: A pointer to the string to be tokenized.
 * @a: An array to store the resulting tokens
*/
void token(char *r, char *a[])
{
int i = 0;
char *t = strtok(r, " \t\n;");
while (t != NULL && i < BUFFER_SIZE)
{
a[i++] = t;
t = strtok(NULL, " \t\n;");
}
a[i] = NULL;
}
/**
 * execute - Execute a command.
 * @a: An array containing the command and its arguments.
 */
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
/**
 * execute_commands - Execute a series of commands.
 * @commands: An array of command strings.
 */
void execute_commands(char *commands[])
{
int i = 0;
while (commands[i] != NULL)
{
char *args[BUFFER_SIZE];
token(commands[i], args);
if (args[0] != NULL)
{
execute(args);
}
i++;
}
}
/**
 * execute_commands_interactive - Execute interactive commands.
 * @commands: An array of command strings.
 */
void execute_commands_interactive(char *commands[])
{
int i = 0;
int result = 0;
while (commands[i] != NULL)
{
char *args[BUFFER_SIZE];
token(commands[i], args);
if (args[0] != NULL)
{
pid_t p = fork();
if (p == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (p == 0)
{
execvp(args[0], args);
perror("execvp");
exit(EXIT_FAILURE);
}
else
{
int s;
wait(&s);
if (WIFEXITED(s))
{
result = WEXITSTATUS(s);
}
}
}
if (strstr(commands[i], "&&") && result != 0)
{
break;
}
else if (strstr(commands[i], "||") && result == 0)
{
break;
}
i++;
}
}
/**
 * remove_comment - Removes comments from a string.
 * @buffer: A pointer to the string to remove comments from.
 */
void remove_comment(char *buffer)
{
char *comment = strchr(buffer, '#');
if (comment != NULL)
{
*comment = '\0';
}
}

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

#define BUFFER_SIZE 1024

/**
 * main - The main function for the shell program.
 * This function continuously prompts the user for input and executes commands.
 * If the user enters "exit", the program will exit.
 * Return: Always returns 0 to indicate successful execution.
 */


int main(void)
{
    char buffer[BUFFER_SIZE];
    char *a[BUFFER_SIZE];
     char *c_dir;
     char *n_dir;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, ":) ", 3);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            break;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "exit") == 0)
        {
            exit(0);
        }
        else if (strncmp(buffer, "exit ", 5) == 0)
        {
        int status = atoi(buffer + 5);
        exit(status);
        }
        else if (strncmp(buffer, "setenv ", 7) == 0)
        {
            char *var_st = strstr(buffer, " ") + 1;
            char *var_end = strstr(var_st, " ") - 1;
            char *val_st = var_end + 2;
            if (var_st != NULL && var_end != NULL && val_st != NULL)
            {
                *var_end = '\0';
                if (setenv(var_st, val_st, 1) != 0) {
                    fprintf(stderr, "Error setting environment variable.\n");
                }
            }
            else
            {
                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            }
        }
        else if (strncmp(buffer, "unsetenv ", 9) == 0)
        {
            char *var = buffer + 9;
            if (var != NULL) {
                if (unsetenv(var) != 0)
                {
                    fprintf(stderr, "Error unsetting environment variable.\n");
                }
            }
            else
            {
                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
            }
        }
         else if (strncmp(buffer, "cd ", 3) == 0 || strcmp(buffer, "cd") == 0)
         {
            char *dir = buffer + 3;
            if (!dir || strcmp(dir, "") == 0)
            {
                dir = getenv("HOME");
            }
            if (strcmp(dir, "-") == 0)
            {
                dir = getenv("OLDPWD");
            }
            c_dir = getcwd(NULL, 0);
            if (c_dir)
            {
                if (chdir(dir) != 0)
                {
                    fprintf(stderr, "cd: no such file or directory: %s\n", dir);
                }
                else
                {
                    setenv("OLDPWD", c_dir, 1);
                    free(c_dir);
                     n_dir = getcwd(NULL, 0);
                    setenv("PWD", n_dir, 1);
                    free(n_dir);
                }
            }
            else
            {
                perror("getcwd");
            }
        }
        else if (strcmp(buffer, "env") == 0)
        {
            char **env = environ;
            while (*env)
            {
                write(STDOUT_FILENO, *env, strlen(*env));
                write(STDOUT_FILENO, "\n", 1);
                env++;
            }
        }
        else
        {
            token(buffer, a);

            if (a[0] != NULL)
            {
                execute(a);
            }
        }
    }

    return (0);
}

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

extern char **environ;
extern int last_exit_status;

#define BUFFER_SIZE 1024

void token(char *r, char *a[]);
void execute(char *a[]);
void execute_commands_interactive(char *commands[]);
void execute_commands(char *commands[]);
void remove_comment(char *buffer);

#endif /* MAIN_H */

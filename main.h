#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

#define BUFFER_SIZE 1024

void token(char *r, char *a[]);
void execute(char *a[]);
void execute_commands(char *commands[]);

#endif /* MAIN_H */

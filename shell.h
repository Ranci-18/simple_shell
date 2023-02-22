#ifndef SHELL_H

#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void print_prompt(void);
char *read_input(void);
void *mrealloc(void *p, unsigned int prev_size, unsigned int new_size);
char **tokenize(char *input, char *delimeter);
char *get_command_path(char **command, char **arguments);
char **env_path(char **env);
int execute(char **commands);
char *length(char *str);
int compare(char *varname, char *dirname);
char *_getenv(char **environ, char *dirname);


#endif

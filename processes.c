#include "shell.h"
/**
 *execute - processes commands and line arguments
 *@commands: passed commands
 *
 *Return: nothing
 */
int execute(char **commands)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(commands[0], commands, NULL) == -1)
		{
			perror(commands[0]);
			exit(1);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("Error:");
	}
	return (0);
}

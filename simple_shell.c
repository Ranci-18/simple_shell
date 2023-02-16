#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#define BUFSIZE 100
/**
 *main - emulates a simple shell
 *
 *
 *Return: nothing
 */
int main(void)
{
	char buf[BUFSIZE];
	pid_t pid;
	char *args[BUFSIZE], *token;
	int status, i = 0;

	while (1)
	{
		printf("($) ");

	if (fgets(buf, BUFSIZE, stdin) == NULL)
	{
		printf("\n");
		return (0);
	}
	token = strtok(buf, " \n");
	if (token == NULL)
	{
		continue;
	}
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;

	pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args);
		printf("./hsh: %s: command not found\n", args[0]);
		return (0);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		wait(&status);
	}
	}
	return (0);
}

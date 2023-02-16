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
	char args[BUFSIZE];
	int status;

	while (1)
	{
		printf("($) ");

	if (fgets(buf, BUFSIZE, stdin) == NULL)
	{
		printf("\n");
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		strcpy(args, buf);
		args[strlen(args) - 1] = '\0';
		execlp(args, args, (char *)NULL);
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

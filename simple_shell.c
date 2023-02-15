#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define BUFSIZE 100
/**
 *
 *
 *
 *
 */
int main()
{
	char buf[BUFSIZE];

	while (1)
	{
		print("($) ");

	if (fgets(buf, BUFSIZE, stdin) == NULL)
	{
		printf("\n");
		return (0);
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		char *args[] = {buf, NULL};
		execvp(buf, args);
		printf("Error: command not found\n");
		return (0);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		int status;
		wait(&status);
	}
	}
	return (0);
}

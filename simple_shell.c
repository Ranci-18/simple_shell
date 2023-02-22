#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#define BUFSIZE 100
/**
 *main - emulates a simple shell
 *
 *
 *Return: nothing
 */
int main(void)
{
	char buf[BUFSIZE], *token, *args[BUFSIZE], *path_token, *path, cmd[BUFSIZE], *envp[] = { NULL }, cwd[PATH_MAX];
	pid_t pid;
	int status, exists, i;

	setenv("PATH", "/bin:/usr/bin", 1);
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd() error");
			return (1);
		}
		printf(":) ");
		if (fgets(buf, BUFSIZE, stdin) == NULL)
		{
			printf("\n");
			return (0);
		}
		if (strcmp(buf, "exit\n") == 0)
			return (0);
		
		exists = 0;
		token = strtok(buf, " \n");
		if (token == NULL)
		{
			continue;
		}
		i = 0;
		while (token != NULL)
		{
			args[i] = token;
			i++;
			token = strtok(NULL, " \n");
		}
		args[i] = NULL;
		
		if (args[0][0] == '/')
		{
			strcpy(cmd, args[0]);
			if (access(cmd, X_OK) == 0)
			{
				exists = 1;
			}
		}
		else
		{
			path = getenv("PATH");
			path_token = strtok(path, ":");
			while (path_token != NULL && exists == 0)
			{
				strcpy(cmd, path_token);
				strcat(cmd, "/");
				strcat(cmd, args[0]);
				if (access(cmd, X_OK) == 0)
				{
					exists = 1;
					args[0] = cmd;
				}
				path_token = strtok(NULL, ":");
			}
		}
		if (exists == 0)
		{
			printf("./shell: No such file or directory\n");
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, envp) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}

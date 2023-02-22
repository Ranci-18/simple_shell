#include "shell.h"
/**
 *get_command_path - gets the full path of command and arguments
 *@command: array of args
 *@arguments: array of args
 *
 *
 *Return: full path of NULL
 */
char *get_command_path(char **command, char **arguments)
{
	char *args, **cat;
	int i, j, k;
	struct stat status;

	for (i = 0; arguments[i]; i++)
	{
		args = malloc(60);
		strcat(args, arguments[i]);
		strcat(args, "/");
		strcat(args, command[0]);

		if (stat(args, &status) == 0)
		{
			for (k = 0; *command[k] != '\0'; k++)
				;
			cat = malloc(sizeof(char *) * (k + 1));
			cat[k] = NULL;
			cat[0] = strdup(args);

			for (j = 0; command[j]; j++)
				cat[j] = strdup(command[j]);
			execute(cat);
			return (args);
		}
		free(args);
	}
	return (NULL);
}

#include "shell.h"
/**
 * length - checks string length
 * @str: string
 * Return: str
 */

char *length(char *str)
{
	int i;

	for (i = 0; str[i] != '='; i++)
		;
	return (str + i + 1);
}

/**
 * compare - compares two strings
 * @varname: first string
 * @dirname: second string
 * Return: 1
 */

int compare(char *varname, char *dirname)
{
	int i;

	for (i = 0; dirname[i] != '\0'; i++)
	{
		if (dirname[i] != varname[i])
			return (0);
	}
	return (1);
}

/**
 * _getenv - gets path in env
 * @environ: global var
 * @dirname: pointer to dirname
 * Return: final or null
 */

char *_getenv(char **environ, char *dirname)
{
	int k, j;
	char *varname, *final;

	for (j = 0; environ[j]; j++)
	{
		varname = malloc(1024);

		for (k = 0; environ[j][k] != '='; k++)
			varname[k] = environ[j][k];

		if (compare(varname, dirname))
		{
			final = length(environ[j]);
			free(varname);
			return (final);

		}
		free(varname);
	}
	return (NULL);
}

#include "shell.h"
/**
 *env_path - finds path
 *@env: global var environment
 *
 *
 *
 *Return: token path
 */
char **env_path(char **env)
{
	char *path_env, **tokens, *delimeter;

	delimeter = ":";
	path_env = _getenv(env, "PATH");
	tokens = tokenize(path_env, delimeter);
	return (tokens);
}

#include "shell.h"
/**
 *print_prompt - prints prompt
 *
 *
 * 
 *Return: nothing
 */
void print_prompt(void)
{
	static int first_time = 1;
	const char *CLEAR_SCREEN_ANSI;

	if (first_time)
	{
		CLEAR_SCREEN_ANSI = "\x1b[1;1H\x1b[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
		first_time = 0;
	}

	printf(":) ");
}
/**
 *read_input - reads input string/command
 *
 *
 *
 *
 *Return: pointer to the command
 */
char *read_input(void)
{
	char *buf = NULL;
	size_t bufsize = 0;
	int c = 0;

	if (getline(&buf, &bufsize, stdin) == -1)
	{
		free(buf);
		exit(-1);
	}
	c = strlen(buf);
	buf[c - 1] = '\0';
	
	return (buf);
}
/**
 *mrealloc - reallocates memory
 *@p: pointer
 *@prev_size: int
 *@new_size: int
 *
 *
 *Return: null
 */
void *mrealloc(void *p, unsigned int prev_size, unsigned int new_size)
{
	char *n;
	size_t i;

	if (p == NULL)
	{
		n = malloc(new_size);
		return (n);
	}

	if (new_size == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}
	
	if (new_size == prev_size)
	{
		return (p);
	}
	n = malloc(new_size);

	if (n == NULL)
		return (NULL);
	for (i = 0; i < prev_size; i++)
	{
		n[i] = ((char *)p)[i];
	}
	free (p);

	return (n);
}
/**
 *tokenize - splits command line arguments into tokens
 *@input: command line input
 *@delimeter: separator
 *
 *
 *Return: pointer
 */
char **tokenize(char *input, char *delimeter)
{
	char **token;
	int buf = 1024, i = 0;

	token = malloc(sizeof(char *) * buf);
	if (token == NULL)
	{
		exit(99);
	}
	token[i] = strtok(input, delimeter);
	i++;
	while (1)
	{
		token[i] = strtok(NULL, delimeter);
		if (i >= buf)
		{
			buf += buf;
			token = mrealloc(token, buf, buf * (sizeof(char *)));
			if(token == NULL)
			{
				exit(98);
			}
		}
		if (token[i] == NULL)
			break;
		i++;
	}
	return (token);
}
/**
 *main - entry point, emulates shimple shell
 *
 *
 *
 *
 *Return: nothing
 */
int main(int argc, char **argv, char **env)
{
	char *input = NULL, *delimeter = "\t \a\n", *command, **token;
	(void)argc;
	
	token = env_path(env);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		print_prompt();
		input = read_input();
		argv = tokenize(input, delimeter);
		command = get_command_path(argv, token);
		if (command == NULL)
		{
			execute(argv);
		}
		free(input);
		free(argv);
		free(command);
	}
	return (0);
}

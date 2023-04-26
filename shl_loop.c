#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0; /* initialize read variable */
	int builtin_ret = 0; /* initialize builtin return variable */

	while (r != -1 && builtin_ret != -2) /* loop until exit signal */
	{
		clear_info(info); /* clear info structure */
		if (interactive(info)) /* check if shell is interactive */
			_puts("$ "); /* print prompt */
		_eputchar(BUF_FLUSH); /* flush standard error buffer */
		r = get_input(info); /* read user input */
		if (r != -1) /* check if input was read successfully */
		{
			set_info(info, av); /* set command info */
			builtin_ret = find_builtin(info); /* check for built-in command */
			if (builtin_ret == -1)
				find_cmd(info); /* execute command */
		}
		else if (interactive(info))
			_putchar('\n'); /* print new line if interactive shell */
		free_info(info, 0); /* free info structure */
	}
	write_history(info); /* write history to file */
	free_info(info, 1); /* free info structure and its components */
	if (!interactive(info) && info->status)
		exit(info->status); /* exit with status code */
	if (builtin_ret == -2) /* check if exit signal was received */
	{
		if (info->err_num == -1)
			exit(info->status); /* exit with status code */
		exit(info->err_num); /* exit with error number */
	}
	return (builtin_ret); /* return status of built-in command */
}

/**
 * find_builtin - finds a built-in command
 * @info: the parameter & return info struct
 *
 * Return: -1 if built-in not found,
 *         0 if built-in executed successfully,
 *         1 if built-in found but not successful,
 *         -2 if built-in signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1; /* initialize built-in command return variable */
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	}; /* initialize built-in command table */

	for (i = 0; builtintbl[i].type; i++) /* loop through built-in commands */
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
			/* check if command is built-in */
		{
			info->line_count++; /* increment command count */
			built_in_ret = builtintbl[i].func(info); /* execute built-in command */
			break;
		}
	return (built_in_ret); /* return built-in command status */
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

#include "shell.h"

/** Authors: Tsitsi Ndhlovu <tsitsindhlovu211@gmail.com>
 *Akeredolu Olasunkanmi Joshua <akeredolujosh@gmail.com>
*/

/**
  * get_environ - returns a copy of the string array of our environ
  * @info: a struct containing potential arguments to maintain constant function prototype
  * Return: Always returns 0
  */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
  * _unsetenv - Removes an environment variable
  * @info: a struct containing potential arguments to maintain constant function prototype
  * @var: the string containing the env variable property to be removed
  * Return: Returns 1 on successful deletion, otherwise 0
  */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
  * _setenv - Initializes a new environment variable or modifies an existing one
  * @info: a struct containing potential arguments to maintain constant function prototype
  * @var: the string containing the env variable property to be set
  * @value: the string containing the value to set the env variable to
  * Return: Always returns 0
  */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

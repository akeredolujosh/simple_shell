#include "shell.h"

/**
 * Authors:Tsitsi Ndhlovu <tsitsindhlovu211@gmail.com>
 * Akeredolu Olasunkanmi Joshua <akeredolujosh@gmail.com>
*/

/**
  * _myenv - Prints the current environment.
  * @info: Structure containing potential arguments.
  * Used to maintain constant function prototype.
  * Return: Always 0.
*/
int _myenv(info_t *info)
{
print_list_str(info->env);
/* Calls function to print list of environment variables. */
return (0);
}

/**
  * _getenv - Gets the value of an environment variable.
  * @info: Structure containing potential arguments.
  * Used to maintain
  * @name: Environment variable name.
  * Return: The value of the environment variable.
  */
char *_getenv(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node) /* Loops through all environment variables. */
{
p = starts_with(node->str, name);
/* Finds the environment variable that matches the given name. */
if (p && *p) /* If found, return its value. */
return (p);
node = node->next;
}
return (NULL); /* If not found, return NULL. */
}

/**
  * mysetenv - Initializes a new environment variable,
  * or modifies an existing one.
  * @info: Structure containing potential arguments. Used to maintain
  * constant function prototype.
  * Return: Always 0.
  */
int _mysetenv(info_t *info)
{
if (info->argc != 3) /* Checks if the number of arguments is correct. */
{
_eputs("Incorrect number of arguments.\n");
/* Prints error message if incorrect. */
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
	/* Calls function to set environment variable. */
return (0);
return (1);
}
/**
  * _myunsetenv - Removes an environment variable.
  * @info: Structure containing potential arguments.
  * Used to maintain constant function prototype.
  * Return: Always 0.
  */
int _myunsetenv(info_t *info)
{
int i;

if (info->argc == 1) /* Checks if the number of arguments is correct. */
{
_eputs("Too few arguments.\n"); /* Prints error message if incorrect. */
return (1);
}
for (i = 1; i <= info->argc; i++) /* Loops through all arguments. */
_unsetenv(info, info->argv[i]);
/* Calls function to unset environment variable. */

return (0);
}

/**
  * populate_env_list - Populates env linked list.
  * @info: Structure containing potential arguments. Used to maintain
  * constant function prototype.
  * Return: Always 0.
  */
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++) /* Loops through all environment variables. */
add_node_end(&node, environ[i], 0);
/* Adds each environment variable to the linked list. */
info->env = node;
return (0);
}

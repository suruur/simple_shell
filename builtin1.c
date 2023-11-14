#include "shell.h"

/**
 * display_history - Displays the history list, one command per line,
 *                   preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias identified by its string representation.
 * @info: Parameter struct.
 * @str: The string representation of the alias.
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * define_alias - Defines an alias identified by its string representation.
 * @info: Parameter struct.
 * @str: The string representation of the alias.
 * Return: Always 0 on success, 1 on error
 */
int define_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_string - Prints the string representation of an alias.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error
 */
int print_alias_string(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Manages alias commands, mimicking behavior of alias builtin.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias_string(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			define_alias(info, info->argv[i]);
		else
			print_alias_string(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

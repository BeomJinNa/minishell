/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 02:36:00 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 22:44:48 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "builtins.h"
#include "hashtable_ext.h"
#include "terminal_parser.h"

char	**get_keys(t_hashtable *hash, int ignore_null);

static int	export_variable(char *str)
{
	char				*divider;
	t_hashtable*const	hash = get_hashtable(0);

	if (hash == NULL)
		return (1);
	if (!check_valid_identifier(str))
	{
		printf("export: `%s`: not a valid identifier\n", str);
		return (1);
	}
	divider = ft_strchr(str, '=');
	if (divider)
	{
		*divider = '\0';
		++divider;
	}
	else
		divider = NULL;
	if (hashtable_addkey(str, divider, hash))
		return (1);
	return (0);
}

int	builtin_export(char **args)
{
	const size_t		argc = count_args(args);
	t_hashtable*const	hash = get_hashtable(0);
	size_t				idx;
	int					result;
	char				**keys;

	if (hash == NULL)
		return (1);
	if (argc == 0)
	{
		keys = get_keys(hash, 0);
		print_hashtable(hash, keys, "declare -x ", "\"");
		remove_tokens(&keys);
		return (0);
	}
	result = 0;
	idx = 0;
	while (idx < argc)
	{
		result |= export_variable(args[idx]);
		++idx;
	}
	return (result);
}

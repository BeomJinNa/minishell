/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:51:09 by dowon             #+#    #+#             */
/*   Updated: 2023/08/26 12:29:19 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "hashtable_ext.h"
#include "builtins.h"
#include "terminal_parser.h"

char	**get_keys(t_hashtable *hash, int ignore_null);

int	builtin_env(char **args)
{
	t_hashtable*const	hash = get_hashtable(0);
	const size_t		argc = count_args(args);
	char				**keys;

	if (hash == NULL)
		return (1);
	if (argc == 0)
	{
		keys = get_keys(hash, 1);
		print_hashtable(hash, keys, "", "");
		remove_tokens(&keys);
		return (0);
	}
	else
		printf("env: too many arguments\n");
	return (1);
}

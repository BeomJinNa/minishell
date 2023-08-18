/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 04:10:06 by dowon             #+#    #+#             */
/*   Updated: 2023/08/13 16:21:23 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "hashtable_ext.h"
#include <stdio.h>

static int	unset_variable(char *str)
{
	if (check_valid_identifier(str))
	{
		printf("unset: `%s`: not a valid identifier", str);
		return (1);
	}
	hashtable_removekey(str, get_hashtable(0));
	return (0);
}

int	builtin_unset(char **args)
{
	const size_t		argc = count_args(args);
	t_hashtable*const	hash = get_hashtable(0);
	int					result;
	size_t				idx;

	if (argc == 1)
	{
		hashtable_removekey(args[0], hash);
		return (0);
	}
	result = 0;
	idx = 0;
	while (idx < argc)
	{
		result |= unset_variable(args[idx]);
		++idx;
	}
	return (result);
}

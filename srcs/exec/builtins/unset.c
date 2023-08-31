/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 04:10:06 by dowon             #+#    #+#             */
/*   Updated: 2023/08/31 18:07:40 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"
#include "hash.h"

int	builtin_unset(char **args)
{
	const size_t		argc = count_args(args);
	int					result;
	size_t				idx;

	result = 0;
	idx = 0;
	while (idx < argc)
	{
		if (!check_valid_identifier(args[idx]))
		{
			printf("unset: `%s`: not a valid identifier\n", args[idx]);
			result = 1;
		}
		++idx;
	}
	if (result)
		return (result);
	idx = 0;
	while (idx < argc)
	{
		hashtable_removekey(args[idx], get_hashtable(0));
		++idx;
	}
	return (result);
}

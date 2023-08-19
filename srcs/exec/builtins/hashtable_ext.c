/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:52:59 by dowon             #+#    #+#             */
/*   Updated: 2023/08/13 16:46:45 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include <stdio.h>

static int	check_variable(char **str_ptr)
{
	char	*str;

	str = *str_ptr + 1;
	if (*str != '{')
	{
		*str_ptr = str;
		return (0);
	}
	str++;
	if (is_this_variable_character(*str, 1) == 0
		&& is_this_special_character(*str) == 0)
		return (1);
	str++;
	while (*str)
	{
		if (*str == '}' && is_this_valid_name(*str_ptr + 2, str - *str_ptr - 2))
		{
			*str_ptr = str;
			return (0);
		}
		if (is_this_variable_character(*str, 1) == 0)
			return (1);
		str++;
	}
	return (1);
}

int	check_valid_identifier(char *str)
{
	// TODO : check str is valid identifier for environment variable name.
	return (1);
}

void	print_hashtable(t_hashtable *hash, const char *prefix)
{
	t_hashnode			*iter;
	int					idx;

	idx = 0;
	while (idx < hash->size)
	{
		if (hash->table[idx] == NULL)
		{
			++idx;
			continue ;
		}
		iter = hash->table[idx];
		while (iter != NULL)
		{
			printf("%s%s=%s\n", prefix, iter->key, iter->value);
			iter = iter->next;
		}
		++idx;
	}
}

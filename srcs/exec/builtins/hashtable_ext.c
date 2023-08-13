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

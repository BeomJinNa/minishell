/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:52:59 by dowon             #+#    #+#             */
/*   Updated: 2023/08/11 03:56:31 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include <stdio.h>

/*
TODO : pipe merge 이후에 삭제하기
*/
t_hashtable	*get_hashtable(unsigned int init)
{
	static t_hashtable	*hash = (void *)0;

	if (init == 0)
		return (hash);
	hash = init_hashtable(init);
	return (hash);
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

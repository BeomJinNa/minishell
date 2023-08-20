/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:30:22 by bena              #+#    #+#             */
/*   Updated: 2023/08/20 20:07:55 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "s_hash.h"

static void	remove_hashkey(t_hashnode *node);

#include <stdio.h>//TEST
void	remove_hashtable(t_hashtable *hash)
{
	unsigned int	index;

	if (hash == NULL)
		return ;
	index = 0;
	while (index < hash->size)
	{
		if (hash->table[index] != NULL)
		{
			printf("remove index %d\n", index);//TEST
			remove_hashkey(hash->table[index]);
		}
		index++;
	}
	free(hash->table);
	free(hash);
}

static void	remove_hashkey(t_hashnode *node)
{
	const t_hashnode	*next = node->next;

	if (node == NULL)
		return ;
	if (node->key != NULL)
	{
		printf("%s ", node->key);//TEST
		free(node->key);
	}
	if (node->value != NULL)
	{
		printf("%s ", node->value);//TEST
		free(node->value);
	}
	printf("\n");//TEST
	free(node);
	if (next != NULL)
		remove_hashkey(node->next);
}

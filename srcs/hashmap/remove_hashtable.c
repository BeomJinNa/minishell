/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:30:22 by bena              #+#    #+#             */
/*   Updated: 2023/07/11 13:27:26 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

static void	remove_hashkey(t_hashnode *node);

void	remove_hashtable(t_hashtable *hash)
{
	unsigned int	index;

	if (hash == NULL)
		return ;
	index = 0;
	while (index < hash->size)
	{
		if (hash->table[index] != NULL)
			remove_hashkey(hash->table[index]);
		index++;
	}
	free(hash->table);
	free(hash);
}

static void	remove_hashkey(t_hashnode *node)
{
	const t_hashnode	*next = node->next;

	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
	if (next != NULL)
		remove_hashkey(node->next);
}

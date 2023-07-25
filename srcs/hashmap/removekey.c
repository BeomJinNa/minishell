/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removekey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:23:25 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 14:37:02 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "s_hash.h"

unsigned int	djb2(const char *str, unsigned int bucket_size);
int				hash_strcmp(char *s1, char *s2);
static void		flush_node(t_hashnode *node);

void	hashtable_removekey(char *key, t_hashtable *hash)
{
	const unsigned int	address = djb2(key, hash->size);
	t_hashnode			*node;
	t_hashnode			*before;

	node = hash->table[address];
	if (node == NULL)
		return ;
	if (hash_strcmp(node->key, key) == 0)
	{
		hash->table[address] = node->next;
		flush_node(node);
		return ;
	}
	before = node;
	while (before->next != NULL && hash_strcmp(before->next->key, key) != 0)
		before = before->next;
	node = before->next;
	if (node != NULL)
	{
		before->next = node->next;
		flush_node(node);
	}
}

static void	flush_node(t_hashnode *node)
{
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:50:53 by bena              #+#    #+#             */
/*   Updated: 2023/07/11 12:20:48 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

static void			flush_node(t_hashnode *node);
static t_hashtable	*terminate_extension(t_hashtable *old, t_hashtable *new);

t_hashtable	*extend_hashtable(t_hashtable *hash, unsigned int size)
{
	t_hashtable		*newhash;
	unsigned int	index;
	t_hashnode		*node;

	if (hash == NULL)
		return (NULL);
	if (size < hash->size)
		size = hash->size;
	newhash = init_hashtable(size);
	index = 0;
	while (index < hash->size)
	{
		while (hash->table[index] != NULL)
		{
			node = hash->table[index];
			if (hashtable_addkey(node->key, node->value, newhash))
				return (terminate_extension(hash, newhash));
			hash->table[index] = node->next;
			flush_node(node);
		}
		index++;
	}
	free(hash->table);
	free(hash);
	return (newhash);
}

static void	flush_node(t_hashnode *node)
{
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
}

static t_hashtable	*terminate_extension(t_hashtable *old, t_hashtable *new)
{
	remove_hashtable(old);
	remove_hashtable(new);
	return (NULL);
}

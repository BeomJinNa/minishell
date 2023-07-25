/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:50:53 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 14:36:27 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "s_hash.h"

t_hashtable			*init_hashtable(unsigned int size);
void				remove_hashtable(t_hashtable *hash);
int					hashtable_addkey(char *key, char *value, t_hashtable *hash);
static int			migrate_address(unsigned int address,
						t_hashtable *old, t_hashtable *new);
static void			flush_node(t_hashnode *node);
static t_hashtable	*terminate_extension(t_hashtable *old, t_hashtable *new);

t_hashtable	*extend_hashtable(t_hashtable *hash, unsigned int size)
{
	t_hashtable		*newhash;
	unsigned int	index;

	if (hash == NULL)
		return (NULL);
	if (size < hash->size)
		size = hash->size;
	newhash = init_hashtable(size);
	index = -1;
	while (++index < hash->size)
		if (migrate_address(index, hash, newhash))
			return (terminate_extension(hash, newhash));
	free(hash->table);
	free(hash);
	return (newhash);
}

static int	migrate_address(unsigned int address,
				t_hashtable *old, t_hashtable *new)
{
	t_hashnode	*node;
	t_hashnode	*next;

	node = old->table[address];
	while (node != NULL)
	{
		if (hashtable_addkey(node->key, node->value, new))
			return (-1);
		node = node->next;
	}
	node = old->table[address];
	while (node != NULL)
	{
		next = node->next;
		flush_node(node);
		node = next;
	}
	return (0);
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

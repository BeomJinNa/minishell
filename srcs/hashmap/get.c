/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:19:53 by bena              #+#    #+#             */
/*   Updated: 2023/08/20 16:24:51 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "s_hash.h"

unsigned int	djb2(const char *str, unsigned int bucket_size);
int				hash_strcmp(char *s1, char *s2);

char	*hashtable_get(char *key, t_hashtable *hash)
{
	const unsigned int	address = djb2(key, hash->size);
	t_hashnode			*node;

	node = hash->table[address];
	while (node != NULL && hash_strcmp(node->key, key) != 0)
		node = node->next;
	if (node == NULL)
		return (NULL);
	return (node->value);
}

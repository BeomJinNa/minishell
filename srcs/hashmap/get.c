/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:19:53 by bena              #+#    #+#             */
/*   Updated: 2023/07/11 13:18:35 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

int	ft_strcmp(char *s1, char *s2);

char	*hashtable_get(char *key, t_hashtable *hash)
{
	const unsigned int	address = djb2(key, hash->size);
	t_hashnode			*node;

	node = hash->table[address];
	while (node != (void *)0 && ft_strcmp(node->key, key) != 0)
		node = node->next;
	if (node == (void *)0)
		return ((void *)0);
	return (node->value);
}

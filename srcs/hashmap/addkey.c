/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:15:08 by bena              #+#    #+#             */
/*   Updated: 2023/07/11 13:17:32 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hash.h"

int			ft_strcmp(char *s1, char *s2);
static int	flush_node(t_hashnode *node);
static void	attach_node(t_hashnode *node, t_hashnode **empty_space);

int	hashtable_addkey(char *key, char *value, t_hashtable *hash)
{
	t_hashnode			*new_node;
	const unsigned int	address = djb2(key, hash->size);

	new_node = (t_hashnode *)malloc(sizeof(t_hashnode));
	if (new_node == NULL)
		return (-1);
	ft_memset(new_node, 0, sizeof(new_node));
	new_node->key = ft_strdup(key);
	if (new_node->key == NULL)
		return (flush_node(new_node));
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
		return (flush_node(new_node));
	attach_node(new_node, &hash->table[address]);
	return (0);
}

static int	flush_node(t_hashnode *node)
{
	if (node == NULL)
		return (-1);
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
	return (-1);
}

static void	attach_node(t_hashnode *node, t_hashnode **empty_space)
{
	while (*empty_space != NULL
		&& ft_strcmp((*empty_space)->key, node->key) != 0)
		*empty_space = (*empty_space)->next;
	if (*empty_space == NULL)
	{
		*empty_space = node;
		return ;
	}
	node->next = (*empty_space)->next;
	flush_node(*empty_space);
	*empty_space = node;
}

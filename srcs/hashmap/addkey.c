/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:15:08 by bena              #+#    #+#             */
/*   Updated: 2023/07/18 22:10:37 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hash.h"

int					ft_strcmp(char *s1, char *s2);
static t_hashnode	*create_node(char *key, char *value);
static t_hashnode	*flush_node(t_hashnode *node);
static void			attach_node(t_hashnode *node, t_hashnode **empty_space);

int	hashtable_addkey(char *key, char *value, t_hashtable *hash)
{
	t_hashnode			*new_node;
	t_hashnode			**node_to_attach;
	const unsigned int	address = djb2(key, hash->size);

	new_node = create_node(key, value);
	if (new_node == NULL)
		return (-1);
	node_to_attach = &hash->table[address];
	while (*node_to_attach != NULL
		&& ft_strcmp((*node_to_attach)->key, key) != 0)
		node_to_attach = &(*node_to_attach)->next;
	attach_node(new_node, node_to_attach);
	return (0);
}

static t_hashnode	*create_node(char *key, char *value)
{
	t_hashnode			*new_node;

	new_node = (t_hashnode *)malloc(sizeof(t_hashnode));
	if (new_node == NULL)
		return (NULL);
	ft_memset(new_node, 0, sizeof(new_node));
	new_node->key = ft_strdup(key);
	if (new_node->key == NULL)
		return (flush_node(new_node));
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
		return (flush_node(new_node));
	new_node->next = NULL;
	return (new_node);
}

static t_hashnode	*flush_node(t_hashnode *node)
{
	if (node == NULL)
		return (NULL);
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
	return (NULL);
}

static void	attach_node(t_hashnode *new_node, t_hashnode **empty_space)
{
	t_hashnode	*old_node;

	old_node = *empty_space;
	if (old_node == NULL)
	{
		*empty_space = new_node;
		return ;
	}
	new_node->next = old_node->next;
	flush_node(old_node);
	*empty_space = new_node;
}

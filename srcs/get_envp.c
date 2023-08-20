/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:50:23 by bena              #+#    #+#             */
/*   Updated: 2023/08/20 21:41:57 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hash.h"

void		remove_tokens(char ***array_ptr);
static int	get_the_number_of_keys(t_hashtable *hash);
static int	get_size_of_address(t_hashnode *node);
static int	fill_list_from_hashtable(char **list, t_hashtable *hash);
static char	*get_str_from_node(t_hashnode *node);

char	**get_envp(t_hashtable *hash)
{
	char	**output;
	int		size;

	if (hash == NULL)
		return (NULL);
	size = get_the_number_of_keys(hash);
	output = (char **)malloc(sizeof(char *) * (size + 1));
	if (output == NULL)
		return (NULL);
	if (fill_list_from_hashtable(output, hash))
		remove_tokens(&output);
	return (output);
}

static int	get_the_number_of_keys(t_hashtable *hash)
{
	int				count;
	unsigned int	index;

	count = 0;
	index = 0;
	while (index < hash->size)
		count += get_size_of_address(hash->table[index++]);
	return (count);
}

static int	get_size_of_address(t_hashnode *node)
{
	int	output;

	output = 0;
	while (node != NULL)
	{
		if (node->value != NULL)
			output++;
		node = node->next;
	}
	return (output);
}

static int	fill_list_from_hashtable(char **list, t_hashtable *hash)
{
	unsigned int	index;
	t_hashnode		*ptr;

	if (list == NULL || hash == NULL)
		return (-1);
	index = 0;
	while (index < hash->size)
	{
		ptr = hash->table[index];
		while (ptr != NULL)
		{
			if (ptr->value != NULL)
			{
				*list = get_str_from_node(ptr);
				if (*list == NULL)
					return (-1);
				list++;
			}
			ptr = ptr->next;
		}
		index++;
	}
	*list = NULL;
	return (0);
}

static char	*get_str_from_node(t_hashnode *node)
{
	char	*output;
	char	*to;
	char	*from;
	int		size;

	size = ft_strlen(node->key) + ft_strlen(node->value) + 1;
	output = (char *)malloc(sizeof(char) * (size + 1));
	if (output == NULL)
		return (0);
	to = output;
	from = node->key;
	while (*from)
		*to++ = *from++;
	*to++ = '=';
	from = node->value;
	while (*from)
		*to++ = *from++;
	*to = '\0';
	return (output);
}

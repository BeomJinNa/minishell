/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:50:23 by bena              #+#    #+#             */
/*   Updated: 2023/08/24 20:13:46 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hash.h"

void		remove_tokens(char ***array_ptr);
void		sort_memory(void *start, int elem_byte, int size,
				int cmp(void *, void *));
int			compare_token(void *a, void *b);
static int	get_the_number_of_keys(t_hashtable *hash, int ignore_null);
static int	get_size_of_address(t_hashnode *node, int ignore_null);
static int	fill_list_from_hashtable(char **list,
				t_hashtable *hash, int ignore_null);
static char	*get_str_from_node(t_hashnode *node);

char	**get_envp(t_hashtable *hash, int ignore_null)
{
	char	**output;
	int		size;

	if (hash == NULL)
		return (NULL);
	size = get_the_number_of_keys(hash, ignore_null);
	output = (char **)malloc(sizeof(char *) * (size + 1));
	if (output == NULL)
		return (NULL);
	if (fill_list_from_hashtable(output, hash, ignore_null))
		remove_tokens(&output);
	if (output != NULL)
		sort_memory(output, sizeof(char *), size, compare_token);
	return (output);
}

static int	get_the_number_of_keys(t_hashtable *hash, int ignore_null)
{
	int				count;
	unsigned int	index;

	count = 0;
	index = 0;
	while (index < hash->size)
		count += get_size_of_address(hash->table[index++], ignore_null);
	return (count);
}

static int	get_size_of_address(t_hashnode *node, int ignore_null)
{
	int	output;

	output = 0;
	while (node != NULL)
	{
		if (ignore_null == 0 || node->value != NULL)
			output++;
		node = node->next;
	}
	return (output);
}

static int	fill_list_from_hashtable(char **list,
		t_hashtable *hash, int ignore_null)
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
			if (ptr->value != NULL || ignore_null == 0)
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

	size = ft_strlen(node->key);
	if (node->value != NULL)
		size += ft_strlen(node->value) + 1;
	output = (char *)malloc(sizeof(char) * (size + 1));
	if (output == NULL)
		return (0);
	to = output;
	from = node->key;
	while (*from)
		*to++ = *from++;
	if (node->value != NULL)
	{
		*to++ = '=';
		from = node->value;
		while (*from)
			*to++ = *from++;
	}
	*to = '\0';
	return (output);
}

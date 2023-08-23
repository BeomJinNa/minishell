/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:52:59 by dowon             #+#    #+#             */
/*   Updated: 2023/08/23 19:22:56 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "terminal_parser.h"
#include <stdio.h>
#include <libft.h>

int	is_this_valid_name(char *str, int size);
int	is_this_variable_character(char c, int allow_number);
int	is_this_special_character(char c);

int	check_valid_identifier(char *str)
{
	size_t	length;
	char	*token;
	int		result;

	if (ft_strchr(str, '=') == NULL)
		length = ft_strlen(str);
	else
		length = ft_strchr(str, '=') - str;
	token = ft_strdup(str);
	token[length] = '\0';
	if (token == NULL)
		return (-1);
	result = is_this_variable_character(*token, 0)
		& is_this_valid_name(token, length);
	free(token);
	return (result);
}

void	print_hashtable(t_hashtable *hash, const char *prefix, int include_null)
{
	t_hashnode		*iter;
	unsigned int	idx;

	idx = 0;
	while (idx < hash->size)
	{
		if (hash->table[idx] != NULL)
		{
			iter = hash->table[idx];
			while (iter != NULL)
			{
				if (iter->key == NULL)
				{
					if (include_null)
						printf("%s%s\n", prefix, iter->key);
				}
				else if (!is_this_special_character(iter->key[0])
					&& is_this_valid_name(iter->key, ft_strlen(iter->key)))
					printf("%s%s=\"%s\"\n", prefix, iter->key, iter->value);
				iter = iter->next;
			}
		}
		++idx;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:52:59 by dowon             #+#    #+#             */
/*   Updated: 2023/08/31 18:02:05 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "hash.h"
#include "libft.h"

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
	if (token == NULL)
		return (-1);
	token[length] = '\0';
	result = is_this_variable_character(*token, 0)
		& is_this_valid_name(token, length);
	free(token);
	return (result);
}

void	print_hashtable(t_hashtable	*hash, char **keys,
	const char *prefix, const char *wrapper)
{
	char			*value;
	size_t			idx;

	idx = 0;
	if (hash == NULL || keys == NULL)
		return ;
	while (keys[idx] != NULL)
	{
		if (*keys[idx] == '\0')
		{
			++idx;
			continue ;
		}
		value = hashtable_get(keys[idx], hash);
		if (value == NULL)
		{
			printf("%s%s\n", prefix, keys[idx]);
		}
		else if (!is_this_special_character(*keys[idx])
			&& is_this_valid_name(keys[idx], ft_strlen(keys[idx])))
			printf("%s%s=%s%s%s\n", prefix, keys[idx],
				wrapper, value, wrapper);
		++idx;
	}
}

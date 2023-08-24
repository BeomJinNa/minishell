/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:59:58 by bena              #+#    #+#             */
/*   Updated: 2023/08/25 03:45:51 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

void		remove_tokens(char ***array_ptr);
char		*va_strndup(const char *str, size_t max_len);
static char	*get_string_to_replace(char *str);
static char	*dup_replaced_string(char *key);

void	replace_variables(char ***tokens_ptr)
{
	char	**ptr;
	char	*str;

	if (tokens_ptr == NULL || *tokens_ptr == NULL)
		return ;
	ptr = *tokens_ptr;
	while (*ptr != NULL)
	{
		if (**ptr == '$' && *(*ptr + 1) != '\0')
		{
			str = *ptr + 1;
			str = get_string_to_replace(str);
			if (str == NULL)
			{
				return (remove_tokens(tokens_ptr));
			}
			free(*ptr);
			*ptr = str;
		}
		ptr++;
	}
}

static char	*get_string_to_replace(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr && *ptr != '}')
		ptr++;
	if (*str == '{')
	{
		str++;
		*ptr = '\0';
	}
	return (dup_replaced_string(str));
}

static char	*dup_replaced_string(char *key)
{
	char	*output;
	char	*value;
	size_t	size;

	value = hashtable_get(key, get_hashtable(0));
	if (value == NULL)
		value = "";
	size = 0;
	while (value[size] != '\0')
		size++;
	output = va_strndup(value, size);
	return (output);
}

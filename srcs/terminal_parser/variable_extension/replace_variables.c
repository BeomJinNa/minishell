/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:59:58 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 17:46:43 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		remove_tokens(char ***array_ptr);
static char	*get_string_to_replace(char *str);
static char	*example_function(char *str);

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
	while (*ptr)
		ptr++;
	if (*str == '{')
	{
		str++;
		*ptr = '\0';
	}
	return (example_function(str));//NEED_TO_REPLACE_THIS
}

static char	*example_function(char *str)
{
	char	*output;
	char	sample[7] = "sample";
	int		i;

	output = (char *)malloc(sizeof(char) * 7);
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i <= 7)
	{
		output[i] = sample[i];
		i++;
	}
	return (output);
}

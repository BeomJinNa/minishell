/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:29:50 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 19:52:59 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			is_this_special_variable(char *str);
int			is_this_variable_character(char c, int allow_number);
int			push_to_end_of_variable(char **str_ptr);
char		*va_strndup(const char *str, size_t max_len);
void		remove_tokens(char ***array_ptr);
static int	get_number_of_tokens(char *str);
static int	push_to_end_of_token(char **str_ptr);
static char	*get_next_token(char **str_ptr);

char	**divide_variables_heredoc(char *str)
{
	char	**output;
	char	**ptr;
	int		size;

	size = get_number_of_tokens(str);
	output = (char **)malloc(sizeof(char *) * (size + 1));
	if (output == NULL)
		return (NULL);
	ptr = output;
	while (ptr - output < size)
	{
		*ptr = get_next_token(&str);
		if (*ptr == NULL)
		{
			remove_tokens(&output);
			return (NULL);
		}
		ptr++;
	}
	*ptr = NULL;
	return (output);
}

static int	get_number_of_tokens(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		push_to_end_of_token(&str);
		count++;
		if (*str == '$')
		{
			push_to_end_of_variable(&str);
			count++;
		}
	}
	return (count);
}

static int	push_to_end_of_token(char **str_ptr)
{
	int		output;
	char	*ptr;

	ptr = *str_ptr;
	while (*ptr != '\0' && *ptr != '$')
		ptr++;
	output = ptr - *str_ptr;
	*str_ptr = ptr;
	return (output);
}

static char	*get_next_token(char **str_ptr)
{
	char	*ptr;
	char	*output;

	ptr = *str_ptr;
	if (*ptr == '$')
		output = va_strndup(*str_ptr, push_to_end_of_variable(&ptr));
	else
	{
		while (*ptr != '\0' && *ptr != '$')
			ptr++;
		output = va_strndup(*str_ptr, ptr - *str_ptr);
	}
	*str_ptr = ptr;
	return (output);
}

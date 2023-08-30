/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:29:50 by bena              #+#    #+#             */
/*   Updated: 2023/08/30 21:05:32 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../brace.h"

int			is_this_special_variable(char *str);
int			is_this_variable_character(char c, int allow_number);
int			push_to_end_of_variable(char **str_ptr);
char		*va_strndup(const char *str, size_t max_len);
void		remove_tokens(char ***array_ptr);
static int	get_number_of_tokens(char *str, t_brace *brace);
static int	push_to_end_of_token(char **str_ptr, t_brace *brace);
static char	*get_next_token(char **str_ptr, t_brace *brace);

char	**divide_variables(char *str)
{
	char	**output;
	char	**ptr;
	int		size;
	t_brace	brace;

	init_brace(&brace, NULL);
	size = get_number_of_tokens(str, &brace);
	init_brace(&brace, NULL);
	output = (char **)malloc(sizeof(char *) * (size + 1));
	if (output == NULL)
		return (NULL);
	ptr = output;
	while (ptr - output < size)
	{
		*ptr = get_next_token(&str, &brace);
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

static int	get_number_of_tokens(char *str, t_brace *brace)
{
	int	count;

	count = 0;
	while (*str)
	{
		push_to_end_of_token(&str, brace);
		count++;
		if (*str == '$')
		{
			push_to_end_of_variable(&str);
			count++;
		}
	}
	return (count);
}

static int	push_to_end_of_token(char **str_ptr, t_brace *brace)
{
	int		output;
	char	*ptr;

	ptr = *str_ptr;
	while (*ptr)
	{
		if (*ptr == '\'' && brace->in_double_brace == 0)
			brace->in_brace ^= 1;
		else if (*ptr == '\"' && brace->in_brace == 0)
			brace->in_double_brace ^= 1;
		if (*ptr == '$' && brace->in_brace == 0)
			break ;
		ptr++;
	}
	output = ptr - *str_ptr;
	*str_ptr = ptr;
	return (output);
}

static char	*get_next_token(char **str_ptr, t_brace *brace)
{
	char	*ptr;
	char	*output;

	ptr = *str_ptr;
	if (*ptr == '$')
		output = va_strndup(*str_ptr, push_to_end_of_variable(&ptr));
	else
	{
		while (*ptr)
		{
			if (*ptr == '\'' && brace->in_double_brace == 0)
				brace->in_brace ^= 1;
			else if (*ptr == '\"' && brace->in_brace == 0)
				brace->in_double_brace ^= 1;
			if (*ptr == '$' && brace->in_brace == 0)
				break ;
			ptr++;
		}
		output = va_strndup(*str_ptr, ptr - *str_ptr);
	}
	*str_ptr = ptr;
	return (output);
}

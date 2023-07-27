/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:29:50 by bena              #+#    #+#             */
/*   Updated: 2023/07/26 16:45:54 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_this_special_variable(char *str);
int	is_this_variable_character(char c, int allow_number);

char	**divide_variables(char *str)
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
		*ptr++ = get_next_token(&str);
	*ptr = NULL;
	return (output);
}

static int	get_number_of_tokens(char *str)
{
	int	in_brace;
	int	in_double_brace;
	int	count;

	in_brace = 0;
	in_double_brace = 0;
	count = 0;
	while (*str)
	{
		if (*str == '\'' && in_double_brace == 0)
			in_brace ^= 1;
		else if (*str == '\"' && in_brace == 0)
			in_double_brace ^= 1;
		if (*str == '$' && in_brace == 0)
			count += push_to_end_of_variable(&str);
		str++;
	}
	return (count);
}

static int	push_to_end_of_variable(char **str_ptr)
{
	char	*ptr;

	return (1);// 무조건 리턴은 1(카운트 값)
}

static char	*get_next_token(char **str_ptr)
{
}

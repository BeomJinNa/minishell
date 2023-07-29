/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:57:57 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 17:52:21 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../brace.h"

static int	get_remaining_string_length(char *str);
static void	take_remaining_string(char *remain, char *original);
static void	scan_redirection(int *flag, char **ptr);

char	*remove_redirections(char *str)
{
	char	*output;
	int		size;

	if (str == NULL)
		return (NULL);
	size = get_remaining_string_length(str);
	output = (char *)malloc(sizeof(char) * (size + 1));
	if (output == NULL)
		return (NULL);
	take_remaining_string(output, str);
	free(str);
	return (output);
}

static int	get_remaining_string_length(char *str)
{
	t_brace	brace;

	init_brace(&brace, str);
	while (*brace.ptr)
	{
		if (*brace.ptr == '\'' && brace.in_double_brace == 0)
			brace.in_brace ^= 1;
		else if (*brace.ptr == '\"' && brace.in_brace == 0)
			brace.in_double_brace ^= 1;
		if (brace.in_brace == 0 && brace.in_double_brace == 0)
			scan_redirection(&brace.on_redirection, &brace.ptr);
		if (brace.on_redirection == 0)
			brace.count++;
		brace.ptr++;
	}
	return (brace.count);
}

static void	take_remaining_string(char *remain, char *original)
{
	char	*ptr_from;
	char	*ptr_to;
	t_brace	brace;

	ptr_from = original;
	ptr_to = remain;
	init_brace(&brace, NULL);
	while (*ptr_from)
	{
		if (*ptr_from == '\'' && brace.in_double_brace == 0)
			brace.in_brace ^= 1;
		else if (*ptr_from == '\"' && brace.in_brace == 0)
			brace.in_double_brace ^= 1;
		if (brace.in_brace == 0 && brace.in_double_brace == 0)
			scan_redirection(&brace.on_redirection, &ptr_from);
		if (brace.on_redirection == 0)
			*ptr_to++ = *ptr_from;
		ptr_from++;
	}
	*ptr_to = '\0';
}

static void	scan_redirection(int *flag, char **ptr)
{
	if (*flag == 1 && **ptr == ' ')
		*flag = 0;
	if (*flag == 0 && (**ptr == '<' || **ptr == '>'))
	{
		*flag = 1;
		while (**ptr == '<' || **ptr == '>')
			(*ptr)++;
		while (**ptr == ' ')
			(*ptr)++;
	}
}

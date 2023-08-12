/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:26:02 by bena              #+#    #+#             */
/*   Updated: 2023/08/12 12:00:49 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "brace.h"

void		remove_board(char ****board_ptr);
void		remove_tokens(char ***array_ptr);
static char	*get_erased_string(char *old);
static int	get_size_of_erased_string(char *str);
static void	dup_erased_string(char *new, char *old);

int	remove_quotes_board(char ****board_ptr)
{
	char	***ptr;
	char	**ptr_sub;
	char	*str;

	if (board_ptr == NULL || *board_ptr == NULL)
		return (1);
	ptr = *board_ptr;
	while (*ptr != NULL)
	{
		ptr_sub = *ptr;
		while (*ptr_sub != NULL)
		{
			str = get_erased_string(*ptr_sub);
			if (str == NULL)
			{
				remove_board(board_ptr);
				return (-1);
			}
			free(*ptr_sub);
			*ptr_sub = str;
			ptr_sub++;
		}
		ptr++;
	}
	return (0);
}

int	remove_quotes_tokens(char ***tokens_ptr)
{
	char	**ptr;
	char	*str;

	if (tokens_ptr == NULL || *tokens_ptr == NULL)
		return (1);
	ptr = *tokens_ptr;
	while (*ptr != NULL)
	{
		str = get_erased_string(*ptr);
		if (str == NULL)
		{
			remove_tokens(tokens_ptr);
			return (-1);
		}
		free(*ptr);
		*ptr = str;
		ptr++;
	}
	return (0);
}

static char	*get_erased_string(char *old)
{
	char	*new;
	int		size;

	size = get_size_of_erased_string(old);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	dup_erased_string(new, old);
	return (new);
}

static int	get_size_of_erased_string(char *str)
{
	int		count;
	t_brace	brace;

	count = 0;
	init_brace(&brace, NULL);
	while (*str)
	{
		if (*str == '\'' && brace.in_double_brace == 0)
			brace.in_brace ^= 1;
		else if (*str == '\"' && brace.in_brace == 0)
			brace.in_double_brace ^= 1;
		if (
			(*str != '\'' && *str != '\"')
			|| (*str == '\'' && brace.in_double_brace == 1)
			|| (*str == '\"' && brace.in_brace == 1)
		)
			count++;
		str++;
	}
	return (count);
}

static void	dup_erased_string(char *new, char *old)
{
	t_brace	brace;

	init_brace(&brace, NULL);
	while (*old)
	{
		if (*old == '\'' && brace.in_double_brace == 0)
			brace.in_brace ^= 1;
		else if (*old == '\"' && brace.in_brace == 0)
			brace.in_double_brace ^= 1;
		if (
			(*old != '\'' && *old != '\"')
			|| (*old == '\'' && brace.in_double_brace == 1)
			|| (*old == '\"' && brace.in_brace == 1)
		)
			*new++ = *old;
		old++;
	}
	*new = '\0';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:39:30 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 19:47:12 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "brace.h"

void		dup_redirection(t_brace *brace, char **node);
void		remove_board(char ****board_ptr);
static int	get_number_of_redirections(char *str);
static void	scan_redirection(t_brace *brace);
static void	write_redirections_board(char ****board, char *str);
static int	copy_node(char ***node_ptr, char **from);

char	***extract_redirections(char *str)
{
	char	***output;
	char	***ptr;
	int		number_of_redirections;

	if (str == NULL)
		return (NULL);
	number_of_redirections = get_number_of_redirections(str);
	output = (char ***)malloc(sizeof(char **) * (number_of_redirections + 1));
	if (output == NULL)
		return (NULL);
	ptr = output;
	while (ptr - output <= number_of_redirections)
		*ptr++ = NULL;
	write_redirections_board(&output, str);
	return (output);
}

static int	get_number_of_redirections(char *str)
{
	int		count;
	t_brace	brace;

	init_brace(&brace, str);
	while (*brace.ptr)
	{
		if (*brace.ptr == '\'' && brace.in_double_brace == 0)
			brace.in_brace ^= 1;
		else if (*brace.ptr == '\"' && brace.in_brace == 0)
			brace.in_double_brace ^= 1;
		if (brace.in_brace == 0 && brace.in_double_brace == 0)
			scan_redirection(&brace);
		brace.ptr++;
	}
	return (brace.count);
}

static void	scan_redirection(t_brace *brace)
{
	if (brace->on_redirection == 1 && *brace->ptr == ' ')
		brace->on_redirection = 0;
	if (brace->on_redirection == 0
		&& (*brace->ptr == '<' || *brace->ptr == '>'))
	{
		brace->on_redirection = 1;
		brace->count++;
		while (*brace->ptr == '<' || *brace->ptr == '>')
			brace->ptr++;
		while (*brace->ptr == ' ')
			brace->ptr++;
	}
}

static void	write_redirections_board(char ****board, char *str)
{
	char	***ptr;
	char	*redirection[2];
	t_brace	brace;

	ptr = *board;
	init_brace(&brace, str);
	redirection[0] = NULL;
	while (*brace.ptr)
	{
		if (*brace.ptr == '\'' && brace.in_double_brace == 0)
			brace.in_brace ^= 1;
		else if (*brace.ptr == '\"' && brace.in_brace == 0)
			brace.in_double_brace ^= 1;
		if (brace.in_brace == 0 && brace.in_double_brace == 0)
			dup_redirection(&brace, redirection);
		if (redirection[0] != NULL)
		{
			if (copy_node(ptr, redirection))
				return (remove_board(board));
			ptr++;
		}
		brace.ptr++;
	}
	*ptr = NULL;
}

static int	copy_node(char ***node_ptr, char **from)
{
	char	**to;

	*node_ptr = (char **)malloc(sizeof(char *) * 3);
	if (*node_ptr == NULL)
		return (-1);
	to = *node_ptr;
	to[0] = from[0];
	to[1] = from[1];
	to[2] = NULL;
	from[0] = NULL;
	from[1] = NULL;
	return (0);
}

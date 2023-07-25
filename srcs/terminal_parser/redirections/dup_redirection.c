/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:30:29 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 19:49:55 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "brace.h"

static int	scan_operator(t_brace *brace);
static int	scan_string(t_brace *brace);
static void	get_string(char *to, char *from, int size);

void	dup_redirection(t_brace *brace, char **node)
{
	int		operator_len;
	int		string_len;
	char	*operator;
	char	*string;

	operator = brace->ptr;
	operator_len = scan_operator(brace);
	node[0] = NULL;
	node[1] = NULL;
	if (operator_len == 0)
		return ;
	node[0] = (char *)malloc(sizeof(char) * (operator_len + 1));
	if (node[0] == NULL)
		return ;
	string = brace->ptr;
	string_len = scan_string(brace);
	node[1] = (char *)malloc(sizeof(char) * (string_len + 1));
	if (node[1] == NULL)
	{
		free(node[0]);
		return ;
	}
	get_string(node[0], operator, operator_len);
	get_string(node[1], string, string_len);
}

static int	scan_operator(t_brace *brace)
{
	char	*end;
	int		output;

	output = 0;
	if (*brace->ptr == '<' || *brace->ptr == '>')
	{
		end = brace->ptr;
		while (*end == '<' || *end == '>')
			end++;
		output = end - brace->ptr;
		while (*end == ' ')
			end++;
		brace->ptr = end;
	}
	return (output);
}

static int	scan_string(t_brace *brace)
{
	char	*end;
	int		output;

	end = brace->ptr;
	while (*end)
	{
		if (*end == '\'' && brace->in_double_brace == 0)
			brace->in_brace ^= 1;
		else if (*end == '\"' && brace->in_brace == 0)
			brace->in_double_brace ^= 1;
		if (brace->in_brace == 0 && brace->in_double_brace == 0
				&& *end == ' ')
			break ;
		end++;
	}
	output = end - brace->ptr;
	brace->ptr = end;
	return (output);
}

static void	get_string(char *to, char *from, int size)
{
	while (size-- > 0)
		*to++ = *from++;
	*to = '\0';
}

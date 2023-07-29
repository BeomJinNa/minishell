/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tokens_to_board.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:13:21 by bena              #+#    #+#             */
/*   Updated: 2023/07/24 14:36:47 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		**get_tokenized_array(const char *str, char c);
void		remove_board(char ****board_ptr);
static char	***get_empty_board(char **array);
static char	***destroy_board(char ****board_ptr);

char	***convert_tokens_to_board(char **array, char delimiter)
{
	char	***board;
	char	***ptr;

	if (array == NULL)
		return (NULL);
	board = get_empty_board(array);
	if (board == NULL)
		return (NULL);
	ptr = board;
	while (*array != NULL)
	{
		*ptr = get_tokenized_array(*array, delimiter);
		if (*ptr == NULL)
			return (destroy_board(&board));
		ptr++;
		array++;
	}
	*ptr = NULL;
	return (board);
}

static char	***get_empty_board(char **array)
{
	char	**ptr;
	int		size;
	char	***output;

	size = 0;
	ptr = array;
	while (*ptr != NULL)
		ptr++;
	size = ptr - array;
	if (size == 0)
		return (NULL);
	output = (char ***)malloc(sizeof(char **) * (size + 1));
	return (output);
}

static char	***destroy_board(char ****board_ptr)
{
	remove_board(board_ptr);
	return (NULL);
}

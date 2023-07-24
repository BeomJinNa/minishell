/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_board_and_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:52:18 by bena              #+#    #+#             */
/*   Updated: 2023/07/24 15:42:00 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	remove_board(char ****board_ptr)
{
	char	***board;
	char	***ptr;
	char	**ptr_sub;

	if (*board_ptr == NULL)
		return ;
	board = *board_ptr;
	ptr = board;
	while (*ptr != NULL)
	{
		ptr_sub = *ptr;
		while (*ptr_sub != NULL)
			free(*ptr_sub++);
		free(*ptr++);
	}
	free(board);
	*board_ptr = NULL;
}

void	remove_tokens(char ***array_ptr)
{
	char	**array;
	char	**ptr;

	if (*array_ptr == NULL)
		return ;
	array = *array_ptr;
	ptr = array;
	while (*ptr != NULL)
		free(*ptr++);
	free(array);
	*array_ptr = NULL;
}

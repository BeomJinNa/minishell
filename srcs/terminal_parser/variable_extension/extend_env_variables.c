/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:36 by bena              #+#    #+#             */
/*   Updated: 2023/07/27 14:22:17 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		remove_board(char ****board_ptr);
static char	*get_extended_string(char *old);

void	extend_env_variables(char ***board)
{
	char	***ptr;
	char	**ptr_sub;
	char	*str;

	if (board == NULL)
		return ;
	ptr = board;
	while (*ptr != NULL)
	{
		ptr_sub = *ptr;
		while (*ptr_sub != NULL)
		{
			str = get_extended_string(*ptr_sub);
			if (str == NULL)
				return (remove_board(&board));
			free(*ptr_sub);
			*ptr_sub = str;
			ptr_sub++;
		}
		ptr++;
	}
}

static char	*get_extended_string(char *old)
{
	char	*new;
	char	**tokens;

	tokens = divide_variables(old);
	if (tokens == NULL)
		return (NULL);
	replace_variables(&tokens);
	if (tokens == NULL)
		return (NULL);
	new = merge_tokens(tokens);
	return (new);
}

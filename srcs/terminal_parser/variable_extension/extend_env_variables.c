/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:36 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 19:03:49 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		**divide_variables(char *str);
void		replace_variables(char ***tokens_ptr);
char		*merge_tokens(char **tokens);
void		remove_tokens(char ***array_ptr);
void		remove_board(char ****board_ptr);
static char	*get_extended_string(char *old);

void	extend_env_variables_token(char ***tokens_ptr)
{
	char	**ptr;
	char	*str;

	if (tokens_ptr == NULL)
		return ;
	ptr = *tokens_ptr;
	while (*ptr != NULL)
	{
		str = get_extended_string(*ptr);
		if (str == NULL)
			return (remove_tokens(tokens_ptr));
		free(*ptr);
		*ptr = str;
		ptr++;
	}
}

void	extend_env_variables_board(char ****board_ptr)
{
	char	***ptr;
	char	**ptr_sub;
	char	*str;

	if (board_ptr == NULL || *board_ptr == NULL)
		return ;
	ptr = *board_ptr;
	while (*ptr != NULL)
	{
		ptr_sub = *ptr;
		while (*ptr_sub != NULL)
		{
			str = get_extended_string(*ptr_sub);
			if (str == NULL)
				return (remove_board(board_ptr));
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
	remove_tokens(&tokens);
	return (new);
}

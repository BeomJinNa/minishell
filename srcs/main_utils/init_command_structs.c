/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:28:13 by bena              #+#    #+#             */
/*   Updated: 2023/08/24 16:07:18 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terminal_parser.h"
#include "e_alloc_errors.h"

int			are_any_syntax_errors_in_pipe(const char *str);
int			alloc_command_structs(t_command *buffer, int size, char **tokens);
static int	return_error(int error, char ***tokens_ptr);

int	get_command_structs(t_command **buffer_ptr, char *str)
{
	char	**tokens;
	int		size;
	int		error;

	*buffer_ptr = NULL;
	if (are_any_syntax_errors_in_pipe(str))
		return (M_SYNTAX_ERROR_PIPE);
	tokens = get_tokenized_array(str, '|');
	if (tokens == NULL)
		return (M_MALLOC_FAIL);
	size = 0;
	while (tokens[size] != NULL)
		size++;
	*buffer_ptr = (t_command *)malloc(sizeof(t_command) * size);
	if (*buffer_ptr == NULL)
		return (return_error(M_MALLOC_FAIL, &tokens));
	ft_memset(*buffer_ptr, 0, sizeof(t_command) * size);
	error = alloc_command_structs(*buffer_ptr, size, tokens);
	if (error)
		return (return_error(error, &tokens));
	remove_tokens(&tokens);
	return (size);
}

int	flush_command_structs(int return_value, t_command **buffer_ptr, int size)
{
	int			index;
	t_command	*buffer;

	if (buffer_ptr == NULL || *buffer_ptr == NULL)
		return (return_value);
	buffer = *buffer_ptr;
	index = 0;
	while (index < size)
	{
		if (buffer[index].command != NULL)
			remove_tokens(&buffer[index].command);
		if (buffer[index].redirections != NULL)
			remove_board(&buffer[index].redirections);
		index++;
	}
	free(buffer);
	*buffer_ptr = NULL;
	return (return_value);
}

static int	return_error(int error, char ***tokens_ptr)
{
	if (tokens_ptr != NULL && *tokens_ptr != NULL)
		remove_tokens(tokens_ptr);
	return (error);
}

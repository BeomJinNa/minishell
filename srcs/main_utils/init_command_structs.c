/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:28:13 by bena              #+#    #+#             */
/*   Updated: 2023/08/18 04:22:45 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "terminal_parser.h"
#include "e_alloc_errors.h"

int			alloc_command_structs(t_command *buffer, int size, char **tokens);
static int	return_error(int error, char ***tokens_ptr, t_command **buffer_ptr);

int	get_command_structs(t_command **buffer_ptr, char *str)
{
	char	**tokens;
	int		size;
	int		error;

	*buffer_ptr = NULL;
	tokens = get_tokenized_array(str, '|');
	if (tokens == NULL)
		return (M_MALLOC_FAIL);
	size = 0;
	while (tokens[size] != NULL)
		size++;
	*buffer_ptr = (t_command *)malloc(sizeof(t_command) * size);
	if (*buffer_ptr == NULL)
		return (return_error(M_MALLOC_FAIL, &tokens, NULL));
	error = alloc_command_structs(*buffer_ptr, size, tokens);
	if (error)
		return (return_error(error, &tokens, buffer_ptr));
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

static int	return_error(int error, char ***tokens_ptr, t_command **buffer_ptr)
{
	if (tokens_ptr != NULL && *tokens_ptr != NULL)
		remove_tokens(tokens_ptr);
	if (buffer_ptr != NULL && *buffer_ptr != NULL)
	{
		free(*buffer_ptr);
		*buffer_ptr = NULL;
	}
	return (error);
}

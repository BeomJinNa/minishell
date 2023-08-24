/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_command_structs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 03:16:54 by bena              #+#    #+#             */
/*   Updated: 2023/08/24 20:57:22 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "terminal_parser.h"
#include "e_alloc_errors.h"

int			flush_command_structs(int return_value, t_command **buffer_ptr,
				int size);
static int	alloc_redirections(t_command *buffer, int size, char **tokens);
static int	check_syntax_redirections(t_command *buffer, int index, int *error);
static int	alloc_commands(t_command *buffer, int size, char **tokens);
static int	remove_quotes(t_command *buffer, int size);

int	alloc_command_structs(t_command *buffer, int size, char **tokens)
{
	int	error;

	error = alloc_redirections(buffer, size, tokens);
	if (error)
		return (flush_command_structs(error, &buffer, size));
	error = alloc_commands(buffer, size, tokens);
	if (error)
		return (flush_command_structs(error, &buffer, size));
	error = remove_quotes(buffer, size);
	if (error)
		return (flush_command_structs(error, &buffer, size));
	return (M_SUCCESS);
}

static int	alloc_redirections(t_command *buffer, int size, char **tokens)
{
	int	index;
	int	error;

	index = -1;
	while (++index < size)
	{
		buffer[index].redirections = extract_redirections(tokens[index]);
		if (buffer[index].redirections == NULL)
			return (M_MALLOC_FAIL);
	}
	index = -1;
	while (++index < size)
		if (check_syntax_redirections(buffer, index, &error))
			return (error);
	index = -1;
	while (++index < size)
	{
		extend_env_variables_board(&buffer[index].redirections);
		if (buffer[index].redirections == NULL)
			return (M_MALLOC_FAIL);
	}
	return (M_SUCCESS);
}

static int	check_syntax_redirections(t_command *buffer, int index, int *error)
{
	if (are_any_syntax_errors_in_redirections(buffer[index].redirections))
	{
		*error = M_SYNTAX_ERROR_REDIRECTIONS;
		return (1);
	}
	if (are_any_syntax_errors_in_extensions_board(buffer[index].redirections))
	{
		*error = M_SYNTAX_ERROR_ENV_VARIABLES;
		return (1);
	}
	return (0);
}

static int	alloc_commands(t_command *buffer, int size, char **tokens)
{
	int		index;
	char	*str;

	index = -1;
	while (++index < size)
	{
		str = remove_redirections(tokens[index]);
		if (str == NULL)
			return (M_MALLOC_FAIL);
		tokens[index] = str;
	}
	if (are_any_syntax_errors_in_extensions_token(tokens))
		return (M_SYNTAX_ERROR_ENV_VARIABLES);
	extend_env_variables_token(&tokens);
	if (tokens == NULL)
		return (M_MALLOC_FAIL);
	index = -1;
	while (++index < size)
	{
		buffer[index].command = get_tokenized_array(tokens[index], ' ');
		if (buffer[index].command == NULL)
			return (M_MALLOC_FAIL);
	}
	return (M_SUCCESS);
}

static int	remove_quotes(t_command *buffer, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (remove_quotes_tokens(&buffer[index].command))
			return (M_MALLOC_FAIL);
		if (remove_quotes_board(&buffer[index].redirections))
			return (M_MALLOC_FAIL);
		index++;
	}
	return (M_SUCCESS);
}

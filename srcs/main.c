/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:23:11 by bena              #+#    #+#             */
/*   Updated: 2023/08/12 11:38:08 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "terminal_parser.h"
#include "hash.h"
#include "e_main_errors.h"
#include "main_utils/e_alloc_errors.h"

int			get_command_structs(t_command **buffer_ptr, char *str);
static int	initialize_settings(void);
static int	process_str(char *str);
static void	release_resources(void);
static int	get_converted_error_number(int error, int module);

int	main(int ac, char **av, char **ep)
{
	char	*str;
	int		error;

	(void)ac;//TEST
	(void)av;//TEST
	(void)ep;//TEST
	if (initialize_settings())
	{
		perror("Error: ");
		return (1);
	}
	str = readline("minishell$ ");
	while (str != NULL)
	{
		add_history(str);
		replace_white_spaces(str);
		error = process_str(str);
		if (error)
			perror("Error: ");
		free(str);
		str = readline("minishell$ ");
	}
	release_resources();
	return (0);
}

static int	initialize_settings(void)
{
	if (get_hashtable(4096) == NULL)
		return (1);
	return (0);
}

static void	release_resources(void)
{
	remove_hashtable(get_hashtable(0));
}

static int	process_str(char *str)
{
	t_command	*commands;
	int			error;

	if (get_number_of_tokens(str, '\0') < 0)
		return (M_ERROR_SYNTAX_QUOTE);
	error = get_command_structs(&commands, str);
	if (error < 0)
		return (get_converted_error_number(error, M_MODULE_PARSER));
	/*
	 * Add Instructions HERE
	 */
	return (0);
}

static int	get_converted_error_number(int error, int module)
{
	if (module == M_MODULE_PARSER && error == M_MALLOC_FAIL)
		return (M_ERROR_MALLOC_FAIL);
	if (module == M_MODULE_PARSER && error == M_SYNTAX_ERROR_REDIRECTIONS)
		return (M_ERROR_SYNTAX_REDIRECTION);
	if (module == M_MODULE_PARSER && error == M_SYNTAX_ERROR_ENV_VARIABLES)
		return (M_ERROR_SYNTAX_ENV_VARIABLE);
	return (error);
}

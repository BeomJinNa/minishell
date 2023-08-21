/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:23:11 by bena              #+#    #+#             */
/*   Updated: 2023/08/21 18:59:40 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "exec.h"
#include "terminal_parser.h"
#include "hash.h"
#include "e_main_errors.h"
#include "main_utils/e_alloc_errors.h"

int			get_command_structs(t_command **buffer_ptr, char *str);
int			flush_command_structs(int return_value,
				t_command **buffer_ptr, int size);
int			convert_envp_to_hash(char *row, t_hashtable *hash);
int			initialize_settings(char **envp);
static int	process_str(char *str);
static void	release_resources(void);
static int	get_converted_error_number(int error_code, int module);

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)argc;
	(void)argv;
	if (initialize_settings(envp))
	{
		perror("Error: ");
		return (1);
	}
	str = readline("minishell$ ");
	while (str != NULL)
	{
		if (str[0] != '\0')
		{
			add_history(str);
			replace_white_spaces(str);
			if (process_str(str))
				perror("Error: ");
		}
		free(str);
		str = readline("minishell$ ");
	}
	printf("exit\n");
	release_resources();
	return (0);
}

static void	release_resources(void)
{
	remove_hashtable(get_hashtable(0));
}

static int	process_str(char *str)
{
	t_command	*commands;
	int			size;
	int			result;

	if (get_number_of_tokens(str, '\0') < 0)
		return (M_ERROR_SYNTAX_QUOTE);
	size = get_command_structs(&commands, str);
	if (size < 0)
		return (get_converted_error_number(size, M_MODULE_PARSER));
	result = execute_commands(commands, size);
	flush_command_structs(0, &commands, size);
	return (result);
}

static int	get_converted_error_number(int error_code, int module)
{
	if (module == M_MODULE_PARSER && error_code == M_MALLOC_FAIL)
		return (M_ERROR_MALLOC_FAIL);
	if (module == M_MODULE_PARSER && error_code == M_SYNTAX_ERROR_REDIRECTIONS)
		return (M_ERROR_SYNTAX_REDIRECTION);
	if (module == M_MODULE_PARSER && error_code == M_SYNTAX_ERROR_ENV_VARIABLES)
		return (M_ERROR_SYNTAX_ENV_VARIABLE);
	return (error_code);
}

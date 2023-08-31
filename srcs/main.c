/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:23:11 by bena              #+#    #+#             */
/*   Updated: 2023/08/31 18:32:48 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "libft.h"

int			get_command_structs(t_command **buffer_ptr, char *str);
int			flush_command_structs(int return_value,
				t_command **buffer_ptr, int size);
int			convert_envp_to_hash(char *row, t_hashtable *hash);
int			initialize_settings(char **envp);
static void	shell_loop(void);
static int	process_str(char *str);
static int	get_converted_error_number(int error_code, int module);
static void	print_error(int error_code);

int	main(int argc, char **argv, char **envp)
{
	int				exit_status;
	struct termios	term;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term);
	if (initialize_settings(envp))
	{
		perror(NULL);
		return (1);
	}
	shell_loop();
	printf("exit\n");
	exit_status = ft_atoi(hashtable_get("?", get_hashtable(0)));
	remove_hashtable(get_hashtable(0));
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (exit_status);
}

static void	shell_loop(void)
{
	char			*str;
	int				error;

	str = readline("minishell$ ");
	while (str != NULL)
	{
		if (str[0] != '\0')
		{
			add_history(str);
			replace_white_spaces(str);
			error = process_str(str);
			if (error)
				print_error(error);
		}
		free(str);
		str = readline("minishell$ ");
	}
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
	result = get_converted_error_number(result, M_MODULE_PIPE);
	flush_command_structs(0, &commands, size);
	return (result);
}

static int	get_converted_error_number(int error_code, int module)
{
	if (module == M_MODULE_PARSER && error_code == -1)
		return (M_ERROR_MALLOC_FAIL);
	else if (module == M_MODULE_PARSER && error_code == -2)
		return (M_ERROR_SYNTAX_REDIRECTION);
	else if (module == M_MODULE_PARSER && error_code == -3)
		return (M_ERROR_SYNTAX_ENV_VARIABLE);
	else if (module == M_MODULE_PARSER && error_code == -4)
		return (M_ERROR_SYNTAX_PIPE);
	return (error_code);
}

static void	print_error(int error_code)
{
	t_hashtable *const	hash = get_hashtable(0);

	if (error_code == M_CALL_PERROR)
		perror(NULL);
	else if (error_code == M_ERROR_MALLOC_FAIL)
		write(2, "Malloc failed.\n", 15);
	else if (error_code == M_ERROR_SYNTAX_REDIRECTION)
		write(2, "Syntax error near redirections.\n", 32);
	else if (error_code == M_ERROR_SYNTAX_ENV_VARIABLE)
		write(2, "Syntax error near env variables.\n", 33);
	else if (error_code == M_ERROR_SYNTAX_QUOTE)
		write(2, "Syntax error near quotes.\n", 26);
	else if (error_code == M_ERROR_SYNTAX_PIPE)
		write(2, "Syntax error near '|'.\n", 23);
	if (error_code == M_ERROR_SYNTAX_REDIRECTION
		|| error_code == M_ERROR_SYNTAX_ENV_VARIABLE
		|| error_code == M_ERROR_SYNTAX_QUOTE
		|| error_code == M_ERROR_SYNTAX_PIPE)
		hashtable_addkey("?", "258", hash);
}

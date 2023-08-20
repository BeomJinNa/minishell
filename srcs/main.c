/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:23:11 by bena              #+#    #+#             */
/*   Updated: 2023/08/20 21:35:09 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "exec.h"
#include "terminal_parser.h"
#include "hash.h"
#include "e_main_errors.h"
#include "main_utils/e_alloc_errors.h"

int			get_command_structs(t_command **buffer_ptr, char *str);
int			flush_command_structs(int return_value,
				t_command **buffer_ptr, int size);
int			convert_envp_to_hash(char *row, t_hashtable *hash);
char		**get_envp(t_hashtable *hash);//TEST
static int	initialize_settings(char **envp);
static int	process_str(char *str);
static void	release_resources(void);
static int	get_converted_error_number(int error_code, int module);

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		error;

	if (initialize_settings(envp))
	{
		perror("Error: ");
		return (1);
	}
	//TEST START
	int i = 0;
	t_hashnode *ptr;
	t_hashtable *hash = get_hashtable(0);
	while (i < 4096)
	{
		ptr = hash->table[i];
		while (ptr != NULL)
		{
			printf("%s=%s\n", ptr->key, ptr->value);
			ptr = ptr->next;
		}
		i++;
	}
	char	**list = get_envp(hash);
	remove_hashtable(hash);
	char	**listptr = list;
	while (*listptr != NULL)
		printf("%s\n", *listptr++);
	remove_tokens(&list);
	system ("leaks minishell");
	return (0);
	//TEST END
	/*
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
	*/
}

static int	initialize_settings(char **envp)
{
	char		**ptr;
	t_hashtable	*hash;
	int			fail;

	if (get_hashtable(4096) == NULL)
		return (-1);
	hash = get_hashtable(0);
	if (envp == NULL)
		return (0);
	fail = 0;
	ptr = envp;
	while (*ptr != NULL)
		if (convert_envp_to_hash(*ptr++, hash))
			fail = 1;
	if (fail)
	{
		remove_hashtable(hash);
		return (-1);
	}
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

	if (get_number_of_tokens(str, '\0') < 0)
		return (M_ERROR_SYNTAX_QUOTE);
	size = get_command_structs(&commands, str);
	if (size < 0)
		return (get_converted_error_number(size, M_MODULE_PARSER));
//	execute_commands(commands, size);
	flush_command_structs(0, &commands, size);
	return (0);
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

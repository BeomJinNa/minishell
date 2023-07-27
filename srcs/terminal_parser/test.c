/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:24:24 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 20:01:08 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "terminal_parser.h"
#include "hash.h"

static void	print_board(char ***board);

int	main(void)
{
	char	*str;
	char	**tokens;
	char	***commands;
	char	***redirections;

	printf("=====================================================\n");
	str = readline("command : ");
	while (str != NULL)
	{
		add_history(str);
		replace_white_spaces(str);
		if (get_number_of_tokens(str, ' ') < 0)
			printf("\033[33mquotation marks are not closed.\033[0m\n");
		else
		{
			redirections = extract_redirections(str);
			if (are_any_syntax_errors_in_redirections(redirections))
				printf("\033[33msyntax errors exist in redirection.\033[0m\n");
			else
			{
				str = remove_redirections(str);
				printf("redirection removed : %s\n", str);
				tokens = get_tokenized_array(str, '|');
				commands = convert_tokens_to_board(tokens, ' ');
				remove_tokens(&tokens);
				if (are_any_syntax_errors_in_extensions(commands)
					|| are_any_syntax_errors_in_extensions(redirections))
					printf("\033[33msyntax errors exist near '{'.\033[0m\n");
				else
				{
					//extend_env_variables(commands, redirections)
					remove_quotes(commands);
					remove_quotes(redirections);
					printf("-----------------------------------------------------\n");
					printf("COMMANDS\n");
					print_board(commands);
					remove_board(&commands);
					printf("\nREDIRECTIONS\n");
					print_board(redirections);
				}
			}
			remove_board(&redirections);
		}
		free(str);
		printf("=====================================================\n");
		str = readline("command : ");
	}
	return (0);
}

static void	print_board(char ***board)
{
	char	***ptr;
	char	**ptr_sub;

	ptr = board;
	if (ptr != NULL)
	{
		while (*ptr != NULL)
		{
			ptr_sub = *ptr;
			while (*ptr_sub != NULL)
			{
				printf("%s ", *ptr_sub);
				ptr_sub++;
			}
			printf("\n");
			ptr++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:32:35 by bena              #+#    #+#             */
/*   Updated: 2023/08/19 22:41:56 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_PARSER_H
# define TERMINAL_PARSER_H

typedef struct s_command
{
	char	**command;
	char	***redirections;
}			t_command;

char	**get_tokenized_array(const char *str, char delimiter);
char	***convert_tokens_to_board(char **array, char delimiter);
char	***extract_redirections(char *str);
char	*merge_tokens(char **tokens);
char	*remove_redirections(char *str);
int		remove_quotes_board(char ****board_ptr);
int		remove_quotes_tokens(char ***tokens_ptr);
void	remove_board(char ****board_ptr);
void	remove_tokens(char ***array_ptr);
void	replace_white_spaces(char *str);
int		get_number_of_tokens(const char *str, char delimiter);
int		are_any_syntax_errors_in_redirections(char ***board);
int		are_any_syntax_errors_in_extensions_board(char ***board);
int		are_any_syntax_errors_in_extensions_token(char **tokens);
void	extend_env_variables_token(char ***tokens_ptr);
void	extend_env_variables_board(char ****board_ptr);
char	*extend_one_line_heredoc(char *str);
int		check_extension_syntax(char *str);

#endif

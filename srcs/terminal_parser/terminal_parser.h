/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:32:35 by bena              #+#    #+#             */
/*   Updated: 2023/07/24 19:19:13 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_PARSER_H
# define TERMINAL_PARSER_H

char	**get_tokenized_array(const char *str, char delimiter);
char	***convert_tokens_to_board(char **array, char delimiter);
char	***extract_redirections(char *str);
char	*remove_redirections(char *str);
void	remove_quotes(char ***board);
void	remove_board(char ****board_ptr);
void	remove_tokens(char ***array_ptr);
void	replace_white_spaces(char *str);
int		get_number_of_tokens(const char *str, char delimiter);
int		are_any_syntax_errors_in_redirections(char ***board);
#endif

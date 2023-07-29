/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_one_line_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:30:18 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 20:01:30 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**divide_variables_heredoc(char *str);
int		are_any_syntax_errors_in_heredoc_extension(char **tokens);
void	remove_tokens(char ***array_ptr);
void	replace_variables(char ***tokens_ptr);
char	*merge_tokens(char **tokens);

char	*extend_one_line_heredoc(char *str)
{
	char	**tokens;

	tokens = divide_variables_heredoc(str);
	if (tokens == NULL)
		return (NULL);
	if (are_any_syntax_errors_in_heredoc_extension(tokens))
	{
		remove_tokens(&tokens);
		return (NULL);
	}
	replace_variables(&tokens);
	if (tokens == NULL)
		return (NULL);
	str = merge_tokens(tokens);
	remove_tokens(&tokens);
	return (str);
}

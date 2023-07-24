/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_any_syntax_errors_in_redirections.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:26:02 by bena              #+#    #+#             */
/*   Updated: 2023/07/24 18:43:48 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_syntax(char **redirection);
static int	check_operator(char *str);
static int	check_string(char *str);

int	are_any_syntax_errors_in_redirections(char ***board)
{
	if (board == (void *)0)
		return (0);
	while (*board != (void *)0)
		if (check_syntax(*board++))
			return (1);
	return (0);
}

static int	check_syntax(char **redirection)
{
	if (check_operator(redirection[0]))
		return (1);
	if (check_string(redirection[1]))
		return (1);
	return (0);
}

static int	check_operator(char *str)
{
	if (str[0] == '>' && str[1] == '\0')
		return (0);
	if (str[0] == '<' && str[1] == '\0')
		return (0);
	if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		return (0);
	if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		return (0);
	return (1);
}

static int	check_string(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str == '<' || *str == '>')
			return (1);
		str++;
	}
	return (0);
}

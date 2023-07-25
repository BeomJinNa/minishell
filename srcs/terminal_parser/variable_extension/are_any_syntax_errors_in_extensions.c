/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_any_syntax_errors_in_extensions.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:26:02 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 18:47:09 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_tokens(char **tokens);
static int	check_syntax(char *str);
static int	check_variable(char *str);
static int	is_this_alphanumeric(char c);

int	are_any_syntax_errors_in_extensions(char ***board)
{
	if (board == (void *)0)
		return (0);
	while (*board != (void *)0)
		if (check_tokens(*board++))
			return (1);
	return (0);
}

static int	check_tokens(char **tokens)
{
	while (*tokens != (void *)0)
		if (check_syntax(*tokens++))
			return (1);
	return (0);
}

static int	check_syntax(char *str)
{
	int	in_brace;
	int	in_double_brace;

	in_brace = 0;
	in_double_brace = 0;
	while (*str)
	{
		if (*str == '\'' && in_double_brace == 0)
			in_brace ^= 1;
		if (*str == '\"' && in_brace == 0)
			in_double_brace ^= 1;
		if (*str == '$' && in_brace == 0)
			if (check_variable(str))
				return (1);
		str++;
	}
	return (0);
}

static int	check_variable(char *str)
{
	if (*(++str) != '{')
		return (0);
	if (*(++str) == '}')
		return (1);
	while (is_this_alphanumeric(*str))
		str++;
	if (*str == '}')
		return (0);
	return (1);
}

static int	is_this_alphanumeric(char c)
{
	if ('A' <= c && c <= 'Z')
		return (1);
	if ('a' <= c && c <= 'z')
		return (1);
	if ('0' <= c && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

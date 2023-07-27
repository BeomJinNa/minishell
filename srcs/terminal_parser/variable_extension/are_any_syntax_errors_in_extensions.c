/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_any_syntax_errors_in_extensions.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:26:02 by bena              #+#    #+#             */
/*   Updated: 2023/07/27 15:58:25 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			is_this_special_character(char c);
int			is_this_variable_character(char c, int allow_number);
int			is_this_valid_name(char *str, int size);
static int	check_tokens(char **tokens);
static int	check_syntax(char *str);
static int	check_variable(char **str_ptr);

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
			if (check_variable(&str))
				return (1);
		str++;
	}
	return (0);
}

static int	check_variable(char **str_ptr)
{
	char	*str;

	str = *str_ptr + 1;
	if (*str != '{')
	{
		*str_ptr = str;
		return (0);
	}
	str++;
	if (is_this_variable_character(*str, 1) == 0
		&& is_this_special_character(*str) == 0)
		return (1);
	str++;
	while (*str)
	{
		if (*str == '}' && is_this_valid_name(*str_ptr + 2, str - *str_ptr - 2))
		{
			*str_ptr = str;
			return (0);
		}
		if (is_this_variable_character(*str, 1) == 0)
			return (1);
		str++;
	}
	return (1);
}

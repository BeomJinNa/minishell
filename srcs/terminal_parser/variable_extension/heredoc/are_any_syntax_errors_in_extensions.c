/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_any_syntax_errors_in_extensions.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:26:02 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 19:53:35 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			is_this_special_character(char c);
int			is_this_variable_character(char c, int allow_number);
int			is_this_valid_name(char *str, int size);
static int	check_extension_syntax(char *str);
static int	check_variable(char **str_ptr);

int	are_any_syntax_errors_in_heredoc_extension(char **tokens)
{
	if (tokens == (void *)0)
		return (0);
	while (*tokens != (void *)0)
		if (check_extension_syntax(*tokens++))
			return (1);
	return (0);
}

static int	check_extension_syntax(char *str)
{
	while (*str)
	{
		if (*str == '$')
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

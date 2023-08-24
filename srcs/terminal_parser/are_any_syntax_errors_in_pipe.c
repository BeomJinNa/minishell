/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_any_syntax_errors_in_pipe.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:41:12 by bena              #+#    #+#             */
/*   Updated: 2023/08/24 17:21:31 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int	check_character_sequence(const char **str, char c);
static int	check_str(const char *ptr, char c, int *flag);

int	are_any_syntax_errors_in_pipe(const char *str)
{
	if (str == NULL)
		return (0);
	return (check_character_sequence(&str, '|'));
}

static int	check_character_sequence(const char **str, char c)
{
	const char	*ptr;
	int			flag;

	ptr = *str;
	while (*ptr == ' ')
		ptr++;
	if (*ptr == c)
		return (1);
	flag = 0;
	if (check_str(ptr, c, &flag))
		return (1);
	return (0);
}

static int	check_str(const char *ptr, char c, int *flag)
{
	int			in_brace;
	int			in_double_brace;

	in_brace = 0;
	in_double_brace = 0;
	while (*ptr)
	{
		if (*ptr == '\'' && in_double_brace == 0)
			in_brace ^= 1;
		else if (*ptr == '\"' && in_brace == 0)
			in_double_brace ^= 1;
		if (in_brace == 0 && in_double_brace == 0)
		{
			if (*ptr == c && *flag == 1)
				return (1);
			if (*ptr == c)
				*flag = 1;
			else if (*ptr != ' ')
				*flag = 0;
		}
		ptr++;
	}
	if (*flag == 1)
		return (1);
	return (0);
}

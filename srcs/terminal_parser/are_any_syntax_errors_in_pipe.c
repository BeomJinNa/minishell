/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_any_syntax_errors_in_pipe.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:41:12 by bena              #+#    #+#             */
/*   Updated: 2023/08/24 16:03:55 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int	check_character_sequence(const char **str, char c);

int	are_any_syntax_errors_in_pipe(const char *str)
{
	return (check_character_sequence(&str, '|'));
}

static int	check_character_sequence(const char **str, char c)
{
	const char	*ptr;
	int			in_brace;
	int			in_double_brace;
	int			flag;

	if (str == NULL || *str == NULL)
		return (0);
	in_brace = 0;
	in_double_brace = 0;
	flag = 0;
	ptr = *str;
	while (*ptr)
	{
		if (*ptr == '\'' && in_double_brace == 0)
			in_brace ^= 1;
		else if (*ptr == '\"' && in_brace == 0)
			in_double_brace ^= 1;
		if (in_brace == 0 && in_double_brace == 0)
		{
			if (*ptr == c)
			{
				if (flag == 1)
					return (1);
				else
					flag = 1;
			}
			else
				flag = 0;
		}
		ptr++;
	}
	return (0);
}

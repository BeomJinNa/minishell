/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_white_spaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:13:10 by bena              #+#    #+#             */
/*   Updated: 2023/07/24 17:09:17 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	replace_white_spaces(char *str)
{
	int	in_brace;
	int	in_double_brace;

	in_brace = 0;
	in_double_brace = 0;
	if (str == (void *)0)
		return ;
	while (*str)
	{
		if (*str == '\'' && in_double_brace == 0)
			in_brace ^= 1;
		else if (*str == '\"' && in_brace == 0)
			in_double_brace ^= 1;
		if (13 >= *str && *str >= 9 && in_brace == 0 && in_double_brace == 0)
			*str = ' ';
		str++;
	}
}

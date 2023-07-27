/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:52:41 by bena              #+#    #+#             */
/*   Updated: 2023/07/27 16:21:27 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	variable_strncmp(char *s1, char *s2, int n);

int	is_this_special_character(char c)
{
	if (c == '?')
		return (1);
	return (0);
}

int	is_this_variable_character(char c, int allow_number)
{
	if ('A' <= c && c <= 'Z')
		return (1);
	if ('a' <= c && c <= 'z')
		return (1);
	if (c == '_')
		return (1);
	if (allow_number != 0 && '0' <= c && c <= '9')
		return (1);
	return (0);
}

int	is_this_valid_name(char *str, int size)
{
	int	numbers;
	int	special_name;

	if (size-- <= 0 || (is_this_variable_character(*str, 1) == 0
			&& is_this_special_character(*str) == 0))
		return (0);
	numbers = 0;
	special_name = 0;
	if ('0' <= *str && *str <= '9')
		numbers = 1;
	else if (is_this_special_character(*str))
		special_name = 1;
	str++;
	while (*str && size-- > 0)
	{
		if (special_name == 1)
			return (0);
		if (numbers == 1 && (*str < '0' || '9' < *str))
			return (0);
		if (is_this_variable_character(*str, 1) == 0)
			return (0);
		str++;
	}
	return (1);
}

static int	variable_strncmp(char *s1, char *s2, int n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		if (*c1 == 0)
			return (0);
		c1++;
		c2++;
		n--;
	}
	return (0);
}

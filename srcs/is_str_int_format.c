/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_str_int_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 05:47:21 by bena              #+#    #+#             */
/*   Updated: 2023/08/31 17:06:45 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int	does_str_have_wrong_character(const char *str);
static int	are_any_signs_at_bad_position(const char *str);
static int	get_number_of_digits(const char *str);
static int	is_value_over_int_range(const char *str);

int	is_str_int_format(const char *str)
{
	int			digits;

	if (str == NULL)
		return (0);
	if (does_str_have_wrong_character(str))
		return (0);
	else if (are_any_signs_at_bad_position(str))
		return (0);
	digits = get_number_of_digits(str);
	if (digits < 10)
		return (1);
	else if (digits > 10)
		return (0);
	else if (is_value_over_int_range(str))
		return (0);
	return (1);
}

static int	does_str_have_wrong_character(const char *str)
{
	while (*str)
	{
		if (*str != '+' && *str != '-' && (*str < '0' || '9' < *str))
			return (1);
		str++;
	}
	return (0);
}

static int	are_any_signs_at_bad_position(const char *str)
{
	int	number_found;
	int	count;

	number_found = 0;
	count = 0;
	while (*str)
	{
		if (number_found == 0)
		{
			if (*str == '+' || *str == '-')
				count++;
			if (count >= 2)
				return (1);
			if ('0' <= *str && *str <= '9')
				number_found = 1;
		}
		else if (*str == '+' || *str == '-')
			return (1);
		str++;
	}
	if (number_found == 0)
		return (1);
	return (0);
}

static int	get_number_of_digits(const char *str)
{
	const char	*ptr;

	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	ptr = str;
	while ('0' <= *ptr && *ptr <= '9')
		ptr++;
	return (ptr - str);
}

static int	is_value_over_int_range(const char *str)
{
	const char	int_max[11] = "2147483648";
	int			index;
	int			minus;

	minus = 0;
	if (*str == '-')
		minus = 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	index = 0;
	while (str[index] && index < 10)
	{
		if (index == 9 && minus == 0 && str[index] == '8')
			return (1);
		if ('0' <= str[index] && str[index] < int_max[index])
			return (0);
		else if (int_max[index] < str[index] && str[index] <= '9')
			return (1);
		index++;
	}
	return (0);
}

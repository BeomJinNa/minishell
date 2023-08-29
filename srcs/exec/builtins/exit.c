/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 02:34:42 by dowon             #+#    #+#             */
/*   Updated: 2023/08/29 20:05:28 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "hash.h"
#include "builtins.h"

static int	validate_arg(char *str)
{
	const int	is_op = str[0] == '-' || str[0] == '+';
	int			idx;

	idx = is_op;
	if (str[idx] == '\0')
		return (-1);
	while (str[idx] != '\0')
	{
		if (str[idx] < '0' || '9' < str[idx])
			return (-1);
		idx++;
	}
	return (0);
}

static size_t	get_op_len(char *str)
{
	char*const	start = str;

	while (*str == '-' || *str == '+')
		str++;
	return (str - start);
}

static void	cut_int(char *str)
{
	const size_t	op_len = get_op_len(str);
	const size_t	num_len = ft_strlen(str) - op_len;
	size_t			idx;
	size_t			add;

	if (num_len <= 8)
		return ;
	add = op_len + num_len - 8;
	idx = op_len;
	while (idx < op_len + 8)
	{
		str[idx] = str[add];
		idx++;
		add++;
	}
	str[idx] = '\0';
}

int	builtin_exit(char **args)
{
	const size_t	argc = count_args(args);
	char			*result_str;
	int				result;

	if (argc == 0)
	{
		result_str = hashtable_get("?", get_hashtable(0));
		result = ft_atoi(result_str);
		exit(result);
	}
	if (argc == 1)
	{
		if (validate_arg(args[0]))
		{
			printf("exit: %s: numeric argument required\n", args[0]);
			exit(255);
		}
		cut_int(args[0]);
		exit(ft_atoi(args[0]) % 256);
	}
	printf("exit: too many arguments\n");
	return (1);
}

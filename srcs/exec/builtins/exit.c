/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 02:34:42 by dowon             #+#    #+#             */
/*   Updated: 2023/08/24 21:16:06 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include "builtins.h"

static int	is_strnum(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	const size_t	argc = count_args(args);

	if (argc == 0)
		exit(0);
	if (argc == 1)
	{
		if (!is_strnum(args[0]))
		{
			printf("exit: %s: numeric argument required", args[0]);
			exit(255);
		}
		exit(ft_atoi(args[0]) % 255);
	}
	printf("exit: too many arguments\n");
	return (1);
}

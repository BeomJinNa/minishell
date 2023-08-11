/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 02:34:42 by dowon             #+#    #+#             */
/*   Updated: 2023/08/11 04:41:58 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief check string contains only numeric characters.
 * 
 * @param str 
 * @return int 
 */
static int	is_strnum(char *str)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

/**
 * @brief exit builtin, success : no return value, error : return 1
 * 
 * @param args 
 * @return int 
 */
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
			return (1);
		}
		exit(ft_atoi(args) % 255);
	}
	printf("exit: too many arguments\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:25:53 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 22:44:38 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtins.h"

int	builtin_echo(char **args)
{
	size_t			idx;
	const size_t	argc = count_args(args);
	const int		option_no_nl = !argc || ft_strncmp(args[0], "-n", 3) == 0;

	if (argc == 0)
		printf("\n");
	idx = option_no_nl;
	while (idx < argc)
	{
		printf("%s", args[idx]);
		if (idx + 1 < argc)
			printf(" ");
		++idx;
	}
	if (!option_no_nl)
		printf("\n");
	return (0);
}

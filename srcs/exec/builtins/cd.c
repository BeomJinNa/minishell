/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:43:42 by dowon             #+#    #+#             */
/*   Updated: 2023/08/29 14:49:58 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	builtin_cd(char **args)
{
	const size_t	argc = count_args(args);

	if (argc == 0)
	{
		printf("cd without arguments are not supported\n");
		return (1);
	}
	if (chdir(args[0]) == -1)
	{
		printf("%s: No such file or directory\n", args[0]);
		return (1);
	}
	return (0);
}

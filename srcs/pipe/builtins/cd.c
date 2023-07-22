/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:43:42 by dowon             #+#    #+#             */
/*   Updated: 2023/07/22 12:38:17 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <libft.h>
#include <unistd.h>

/**
 * @brief cd with only a relative or absolute path
 * 
 * @param args 
 * @return int success: 0, error: 1
 */
int	builtin_cd(char **args)
{
	const size_t	argc = count_args(args);

	if (argc == 0)
	{
		ft_putstr_fd("cd without arguments are not supported\n", STDOUT_FILENO);
		return (1);
	}
	if (chdir(args[0]) == -1)
	{
		ft_putstr_fd(args[0], STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

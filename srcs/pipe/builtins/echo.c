/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:25:53 by dowon             #+#    #+#             */
/*   Updated: 2023/07/21 23:29:42 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "builtins.h"
#include <unistd.h>

int	builtin_echo(char **args)
{
	size_t			idx;
	const size_t	argc = count_args(args);
	const int		new_line_option = ft_strncmp(args[0], "-n", 2) == 0;

	idx = new_line_option;
	while (idx < argc)
	{
		ft_putstr_fd(args[idx], STDOUT_FILENO);
		++idx;
	}
}

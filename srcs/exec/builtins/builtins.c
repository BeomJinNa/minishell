/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:29:58 by dowon             #+#    #+#             */
/*   Updated: 2023/08/22 17:35:34 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

int	is_builtin(char *command)
{
	return (
		command
		&& (ft_strncmp(command, "echo", 5) == 0
			|| ft_strncmp(command, "cd", 3) == 0
			|| ft_strncmp(command, "pwd", 4) == 0
			|| ft_strncmp(command, "export", 6) == 0
			|| ft_strncmp(command, "unset", 5) == 0
			|| ft_strncmp(command, "env", 4) == 0
			|| ft_strncmp(command, "exit", 5) == 0)
	);
}

int	run_builtin(char **command)
{
	if (ft_strncmp(command[0], "echo", 5) == 0)
		return (builtin_echo(command + 1));
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		return (builtin_cd(command + 1));
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (builtin_pwd(command + 1));
	else if (ft_strncmp(command[0], "export", 6) == 0)
		return (builtin_export(command + 1));
	else if (ft_strncmp(command[0], "unset", 5) == 0)
		return (builtin_unset(command + 1));
	else if (ft_strncmp(command[0], "env", 4) == 0)
		return (builtin_env(command + 1));
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		return (builtin_exit(command + 1));
	return (-1);
}

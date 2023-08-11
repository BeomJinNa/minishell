/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/08/11 04:59:43 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "terminal_parser.h"
#include "pipe/pipe.h"


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include "pipe/pipe.h"
#include "terminal_parser.h"
#include "hash.h"
#include "pipe/pipe.h"

void	exec_command(char **command)
{
	if (ft_strncmp(command[0], "echo", 4))
		exit(builtin_echo(command + 1));
	else if (ft_strncmp(command[0], "cd", 2))
		exit(builtin_cd(command + 1));
	else if (ft_strncmp(command[0], "pwd", 3))
		exit(builtin_pwd(command + 1));
	else if (ft_strncmp(command[0], "export", 5))
		exit(builtin_export(command + 1));
	else if (ft_strncmp(command[0], "unset", 5))
		exit(builtin_unset(command + 1));
	else if (ft_strncmp(command[0], "env", 3))
		exit(builtin_env(command + 1));
	else if (ft_strncmp(command[0], "exit", 4))
		exit(builtin_exit(command + 1));
	execve(get_excutable_path(get_env("PATH"), command[0]),
		command + 1, get_all_env());
}

int	execute_child(t_command command, int *pipes, int idx)
{
	if (open_redirections(command.redirections,
			readpipe_at(pipes, idx), writepipe_at(pipes, idx + 1)))
		return (-1);
	if (dup_pipes(pipes, idx))
		return (-1);
	exec_command(command.command);
	close_rw_pipes(pipes, idx);
	return (-1);
}

int	fork_n_execute(t_command *commands, int *pipes, int idx, int size)
{
	const pid_t	fork_pid = fork();

	if (fork_pid == -1)
		return (-1);
	if (fork_pid == 0)
	{
		if (execute_child(commands[idx], pipes, idx))
		{
			clean_pipes(pipes, size);
			return (-1);
		}
	}
	else if (close_rw_pipes(pipes, idx))
	{
		clean_pipes(pipes, size);
		return (-1);
	}
	return (0);
}

void	wait_all(int size)
{
	int	idx;
	int	status;

	idx = 0;
	while (idx < size)
	{
		wait(&status);
		if (WIFEXITED(status))
			if (hashtable_addkey("?", WEXITSTATUS(status), env_hash()))
				return (-1);
	}
}

int	execute_commands(t_command *commands, int size)
{
	const int	*pipes = init_pipes(size);
	int			idx;

	if (pipes == NULL)
		return (-1);
	idx = 0;
	while (idx < size)
	{
		if (fork_n_execute(commands, pipes, idx, size))
			return (-1);
		idx++;
	}
	wait_all(size);
	return (0);
}

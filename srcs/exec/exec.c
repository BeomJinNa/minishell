/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/08/21 20:13:16 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include <hash.h>
#include <terminal_parser.h>
#include "pipe/pipe.h"
#include "builtins/builtins.h"
#include "redirection/redirection.h"
#include <libft.h>

void	exec_command(char **command)
{
	char		*exe_path;
	char*const	path_env = hashtable_get("PATH", get_hashtable(0));

	if (is_builtin(command[0]))
		exit(run_builtin(command));
	if (path_env)
		exe_path = get_excutable_path(path_env, command[0]);
	if (path_env == NULL || exe_path == NULL)
	{
		printf("%s : command not found\n", command[0]);
		exit(127);
	}
	execvp(exe_path, command);
}
// execve(exe_path, command, get_hashtable_arr(get_hashtable(0)));

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
		printf("child : %d\n", getpid());
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

static int	wait_all(int size)
{
	int		idx;
	int		status;
	int		exit_status;

	idx = 0;
	while (idx < size)
	{
		printf("child: %d end\n", wait(&status));
		++idx;
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = WTERMSIG(status) + 128;
	}
	return (exit_status);
}

void	set_exit_status(int status)
{
	char*const	status_str = ft_itoa(status);

	hashtable_addkey("?", status_str, get_hashtable(0));
	free(status_str);
}

int	run_single_builtin(t_command *commands, int *pipes)
{
	const int	in = dup(STDOUT_FILENO);
	const int	out = dup(STDIN_FILENO);
	int			result;

	if (open_redirections(commands[0].redirections,
			readpipe_at(pipes, 0), writepipe_at(pipes, 1)))
		return (-1);
	if (dup_pipes(pipes, 0))
		return (-1);
	result = run_builtin(commands[0].command);
	close_rw_pipes(pipes, 0);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	return (result);
}

int	execute_commands(t_command *commands, int size)
{
	int*const	pipes = init_pipes(size);
	int			idx;
	int			result;

	if (pipes == NULL)
		return (-1);
	if (size == 1 && is_builtin(commands[0].command[0]))
		result = run_single_builtin(commands, pipes);
	else
	{
		idx = 0;
		while (idx < size)
		{
			if (fork_n_execute(commands, pipes, idx, size))
				return (-1);
			idx++;
		}
		result = wait_all(size);
	}
	free(pipes);
	set_exit_status(result);
	return (result);
}

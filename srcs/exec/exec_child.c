/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:24:11 by dowon             #+#    #+#             */
/*   Updated: 2023/08/22 18:36:56 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "terminal_parser.h"
#include "redirection/redirection.h"
#include "builtins/builtins.h"
#include "hash.h"
#include "pipe/pipe.h"

static int	execute_child(t_command command, int *pipes, int idx);
static void	exec_command(char **command);
char		**get_envp(t_hashtable *hash);

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
			exit(1);
		}
	}
	else if (close_rw_pipes(pipes, idx))
	{
		clean_pipes(pipes, size);
		return (-1);
	}
	return (0);
}

static void	exec_command(char **command)
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
	execve(exe_path, command, get_envp(get_hashtable(0)));
}

static int	execute_child(t_command command, int *pipes, int idx)
{
	if (open_redirections(command.redirections,
			readpipe_at(pipes, idx), writepipe_at(pipes, idx + 1)))
		return (-1);
	if (dup_pipes(pipes, idx))
		return (-1);
	if (command.command[0][0] == '\0')
		exit(0);
	exec_command(command.command);
	close_rw_pipes(pipes, idx);
	return (-1);
}

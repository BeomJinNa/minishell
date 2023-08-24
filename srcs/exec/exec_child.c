/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:24:11 by dowon             #+#    #+#             */
/*   Updated: 2023/08/25 03:55:26 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include "terminal_parser.h"
#include "redirection/redirection.h"
#include "builtins/builtins.h"
#include "hash.h"
#include "libft.h"
#include "pipe/pipe.h"

static int	execute_child(t_command command, int *pipes, int idx);
static void	exec_command(char **command);
char		**get_envp(t_hashtable *hash, int ignore_null);

int	fork_n_execute(t_command *commands, int *pipes, int idx, int size)
{
	const pid_t	fork_pid = fork();

	if (fork_pid == -1)
		return (-1);
	if (fork_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGKILL, SIG_DFL);
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

static int	is_path_included(char *str)
{
	return (
		ft_strncmp(str, "/", 1) == 0
		|| ft_strncmp(str, "./", 2) == 0
		|| ft_strncmp(str, "../", 3) == 0
	);
}

static void	exec_command(char **command)
{
	int			result;
	char		*exe_path;
	char*const	path_env = hashtable_get("PATH", get_hashtable(0));
	char**const	envp = get_envp(get_hashtable(0), 1);

	if (is_builtin(command[0]))
		result = run_builtin(command);
	else
	{
		exe_path = NULL;
		if (is_path_included(command[0]))
			exe_path = command[0];
		else if (path_env)
			exe_path = get_excutable_path(path_env, command[0]);
		result = execve(exe_path, command, envp);
		remove_tokens((char ***)&envp);
		free(exe_path);
		if (errno == EACCES)
			result = 126;
		else
			result = 127;
	}
	if (result)
		perror(NULL);
	exit(result);
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

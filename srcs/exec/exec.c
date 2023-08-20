/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/08/20 23:44:07 by dowon            ###   ########.fr       */
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
	// char	*exec_path;

	if (ft_strncmp(command[0], "echo", 5) == 0)
		exit(builtin_echo(command + 1));
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		exit(builtin_cd(command + 1));
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		exit(builtin_pwd(command + 1));
	else if (ft_strncmp(command[0], "export", 6) == 0)
		exit(builtin_export(command + 1));
	else if (ft_strncmp(command[0], "unset", 5) == 0)
		exit(builtin_unset(command + 1));
	else if (ft_strncmp(command[0], "env", 4) == 0)
		exit(builtin_env(command + 1));
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		exit(builtin_exit(command + 1));
	// exec_path = hashtable_get("PATH", get_hashtable(0));
	// if (exec_path == NULL)
	// {
	// 	printf("%s : command not found\n", command[0]);
	// 	exit(127);
	// }
	// execve(exec_path, command, get_hashtable_arr(get_hashtable(0)));
	execvp(command[0], command);
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

int	execute_single(t_command command, int *pipes)
{
	exec_command(command.command);
	close_rw_pipes(pipes, 0);
	return (0);
}

static int	wait_all(int size)
{
	int		idx;
	int		status;
	char	*status_str;

	idx = 0;
	while (idx < size)
	{
		wait(&status);
		++idx;
		if (WIFEXITED(status))
		{
			status_str = ft_itoa(WEXITSTATUS(status));
			if (status_str == NULL)
				return (-1);
			if (hashtable_addkey("?", status_str, get_hashtable(0)))
				return (-1);
			free(status_str);
		}
	}
	return (0);
}

int is_builtin(char **command)
{
	return (ft_strncmp(command[0], "echo", 5) == 0
		|| ft_strncmp(command[0], "cd", 3) == 0
		|| ft_strncmp(command[0], "pwd", 4) == 0
		|| ft_strncmp(command[0], "export", 6) == 0
		|| ft_strncmp(command[0], "unset", 5) == 0
		|| ft_strncmp(command[0], "env", 4) == 0
		|| ft_strncmp(command[0], "exit", 5) == 0
	);
}

int run_builtin(char **command)
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

void set_exit_status(int status)
{
	char*const	status_str = ft_itoa(status);

	hashtable_addkey("?", status_str, get_hashtable(0));
	free(status_str);
}

int	execute_commands(t_command *commands, int size)
{
	int*const	pipes = init_pipes(size);
	int			idx;
	int			result;

	if (pipes == NULL)
		return (-1);
	if (size == 1)
	{
		if (is_builtin(commands[0].command))
		{
			int in = dup(STDOUT_FILENO);
			int out = dup(STDIN_FILENO);
			if (open_redirections(commands[0].redirections,
					readpipe_at(pipes, 0), writepipe_at(pipes, 1)))
				return (-1);
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			result = run_builtin(commands[0].command);
		}
		else
		{
			if (fork_n_execute(commands, pipes, 0, size))
				return (-1);
			result = wait_all(size);
		}
	}
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

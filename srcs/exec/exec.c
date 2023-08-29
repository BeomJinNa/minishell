/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/08/29 16:29:39 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include <sys/wait.h>
#include <hash.h>
#include <terminal_parser.h>
#include "pipe/pipe.h"
#include "builtins/builtins.h"
#include <signal.h>

int	fork_n_execute(t_command *commands, int *pipes, int idx, int size);
int	run_single_builtin(t_command *commands, int *pipes);

static int	wait_all(int size, int last_pid)
{
	int		idx;
	int		status;
	int		exit_status;
	pid_t	pid;

	idx = 0;
	exit_status = -1;
	while (idx < size)
	{
		pid = wait(&status);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + 128;
		}
		++idx;
	}
	return (exit_status);
}

void	set_exit_status(int status)
{
	char	*status_str;

	if (status < 0)
		hashtable_addkey("?", "1", get_hashtable(0));
	else
	{
		status_str = ft_itoa(status);
		hashtable_addkey("?", status_str, get_hashtable(0));
		free(status_str);
	}
}

int	on_execute_fail(sig_t old_sigint, sig_t old_sigquit, int *pipes)
{
	if (pipes != NULL)
		free(pipes);
	set_exit_status(1);
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
	return (-1);
}

int	execute_commands(t_command *commands, int size)
{
	int*const	pipes = init_pipes(size);
	int			idx;
	int			result;
	int			last_pid;
	sig_t		signals[2];

	signals[0] = signal(SIGINT, SIG_IGN);
	signals[1] = signal(SIGQUIT, SIG_IGN);
	if (pipes == NULL)
		return (on_execute_fail(signals[0], signals[1], pipes));
	if (size == 1 && is_builtin(commands[0].command[0]))
		result = run_single_builtin(commands, pipes);
	else
	{
		idx = -1;
		while (++idx < size)
		{
			last_pid = fork_n_execute(commands, pipes, idx, size);
			if (last_pid < 0)
				return (on_execute_fail(signals[0], signals[1], pipes));
		}
		result = wait_all(size, last_pid);
	}
	free(pipes);
	set_exit_status(result);
	signal(SIGINT, signals[0]);
	signal(SIGQUIT, signals[1]);
	return (result);
}

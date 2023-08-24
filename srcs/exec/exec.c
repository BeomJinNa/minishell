/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/08/24 21:17:02 by bena             ###   ########.fr       */
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
#include <libft.h>

int	fork_n_execute(t_command *commands, int *pipes, int idx, int size);
int	run_single_builtin(t_command *commands, int *pipes);

static int	wait_all(int size)
{
	int		idx;
	int		status;
	int		exit_status;

	idx = 0;
	while (idx < size)
	{
		wait(&status);
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

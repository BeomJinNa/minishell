/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:29:35 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 22:47:00 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "pipe.h"

int	*readpipe_at(int *pipes, int idx)
{
	return (pipes + (2 * idx + pipe_read));
}

int	*writepipe_at(int *pipes, int idx)
{
	return (pipes + (2 * idx + pipe_write));
}

void	clean_pipes(int *pipes, int process_count)
{
	int	idx;

	idx = 0;
	while (idx <= process_count)
	{
		if (pipes[2 * idx] >= 0 && pipes[2 * idx] != STDIN_FILENO)
			close(pipes[2 * idx]);
		if (pipes[2 * idx + 1] >= 0 && pipes[2 * idx + 1] != STDOUT_FILENO)
			close(pipes[2 * idx + 1]);
		idx++;
	}
	free(pipes);
}

int	*init_pipes(int process_count)
{
	int*const	pipes = malloc(sizeof(int) * ((process_count + 1) * 2));
	int			idx;

	if (pipes == NULL)
		return (NULL);
	idx = 0;
	while (idx < process_count + 1)
	{
		pipes[2 * idx] = -1;
		pipes[2 * idx + 1] = -1;
		idx++;
	}
	pipes[pipe_read] = STDIN_FILENO;
	pipes[2 * process_count + pipe_write] = STDOUT_FILENO;
	idx = 0;
	while (++idx < process_count)
	{
		if (pipe(pipes + (2 * idx)))
		{
			clean_pipes(pipes, process_count);
			return (NULL);
		}
	}
	return (pipes);
}

int	close_rw_pipes(int *pipes, int idx)
{
	if (*readpipe_at(pipes, idx) != STDIN_FILENO)
	{
		if (close(*readpipe_at(pipes, idx)))
			return (-1);
		*readpipe_at(pipes, idx) = -1;
	}
	if (*writepipe_at(pipes, idx + 1) != STDOUT_FILENO)
	{
		if (close(*writepipe_at(pipes, idx + 1)))
			return (-1);
		*writepipe_at(pipes, idx + 1) = -1;
	}
	return (0);
}

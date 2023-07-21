/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:29:35 by dowon             #+#    #+#             */
/*   Updated: 2023/07/21 22:42:10 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include "./builtins/builtins.h"
#include "./pipe.h"

int	readpipe_at(int *pipes, int idx)
{
	return (pipes[2 * idx + pipe_fd_read]);
}

int	writepipe_at(int *pipes, int idx)
{
	return (pipes[2 * idx + pipe_fd_write]);
}

int	*init_pipes(size_t process_count)
{
	int*const	pipes = malloc(sizeof(int) * (process_count * 2 + 2));
	size_t		idx;

	if (pipes == NULL)
	{
		perror("malloc failed\n");
		return (NULL);
	}
	pipes[0] = -1;
	pipes[1] = -1;
	pipes[2 * process_count] = -1;
	pipes[2 * process_count + 1] = -1;
	idx = 1;
	while (idx < process_count)
	{
		pipe(pipes + (2 * idx));
		++idx;
	}
	return (pipes);
}

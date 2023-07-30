/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:29:35 by dowon             #+#    #+#             */
/*   Updated: 2023/07/26 22:57:03 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include "builtins.h"
#include "pipe.h"

int	readpipe_at(int *pipes, int idx)
{
	return (pipes[2 * idx + pipe_fd_read]);
}

int	writepipe_at(int *pipes, int idx)
{
	return (pipes[2 * idx + pipe_fd_write]);
}

/*
# commands, pipe
echo arg1 arg2 "arg3 group" arg4 | cat
{
	{"echo", "arg1", "arg2", "arg3 group", "arg4", NULL},
	{"cat", NULL},
	NULL
}

# redirections
(괄호 사이 공백제거)
<     in >  out >>append <<heredocs
{"<in", ">out", ">>append", "<<heredocs", NULL}

# commands + redirections 합치면
<in echo arg1 arg2 "arg3 group" arg4 | cat > out >>append
redirections : {"<in", ">out", ">>append", NULL},
commands : {
	{"echo", "arg1", "arg2", "arg3 group", "arg4", NULL},
	{"cat", NULL},
	NULL
}
*/
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 01:08:13 by dowon             #+#    #+#             */
/*   Updated: 2023/08/13 17:46:21 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipe.h"


#include <stdio.h>

int	dup_rw_pipes(int *pipes, int idx)
{
	if (*readpipe_at(pipes, idx) != STDIN_FILENO)
		if (dup2(*readpipe_at(pipes, idx), STDIN_FILENO))
			return (-1);
	if (*writepipe_at(pipes, idx + 1) != STDOUT_FILENO)
		if (dup2(*writepipe_at(pipes, idx + 1), STDOUT_FILENO))
			return (-1);
	return (0);
}

int	dup_pipes(int *pipes, int idx)
{
	if (close(*readpipe_at(pipes, idx)))
		return (-1);
	if (dup_rw_pipes(pipes, idx))
		return (-1);
	if (close_rw_pipes(pipes, idx))
		return (-1);
	return (0);
}

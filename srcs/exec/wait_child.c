/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:03:30 by dowon             #+#    #+#             */
/*   Updated: 2023/08/29 20:04:19 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

int	wait_all(int size, int last_pid)
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

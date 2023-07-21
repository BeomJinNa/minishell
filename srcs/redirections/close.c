/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:05:53 by dowon             #+#    #+#             */
/*   Updated: 2023/07/26 23:20:38 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	set_exit_status(int exit_status);

int	close_in(int *fd)
{
	if (*fd != STDIN_FILENO && close(*fd) == -1)
	{
		set_exit_status(1);
		printf("%d: Failed to close\n", *fd);
		return (1);
	}
	*fd = -1;
	return (0);
}

int	close_out(int *fd)
{
	if (*fd != STDOUT_FILENO && close(*fd) == -1)
	{
		set_exit_status(1);
		printf("%d: Failed to close\n", *fd);
		return (1);
	}
	*fd = -1;
	return (0);
}

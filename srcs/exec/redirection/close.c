/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:05:53 by dowon             #+#    #+#             */
/*   Updated: 2023/08/06 19:35:34 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	close_in(int *fd)
{
	if (*fd == STDIN_FILENO)
	{
		*fd = -1;
		return (0);
	}
	if (close(*fd) == -1)
	{
		*fd = -1;
		return (-1);
	}
	*fd = -1;
	return (0);
}

int	close_out(int *fd)
{
	if (*fd == STDOUT_FILENO)
	{
		*fd = -1;
		return (0);
	}
	if (close(*fd) == -1)
	{
		*fd = -1;
		return (-1);
	}
	*fd = -1;
	return (0);
}

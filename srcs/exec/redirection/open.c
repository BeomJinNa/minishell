/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:08:03 by dowon             #+#    #+#             */
/*   Updated: 2023/08/24 20:47:34 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief open filename with option, O_RDONLY
 * 
 * @param filename 
 * @return int 
 */
int	open_read(const char *filename, int *fd)
{
	if (access(filename, F_OK))
	{
		write(STDERR_FILENO, "No such file or directory\n", 27);
		return (-1);
	}
	if (access(filename, R_OK))
	{
		write(STDERR_FILENO, "Permission denied\n", 19);
		return (-1);
	}
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		return (-1);
	return (0);
}

/**
 * @brief open filename with option, O_WRONLY | O_CREAT with 0644
 * 
 * @param filename 
 * @return int 
 */
int	open_write(const char *filename, int *fd)
{
	if (!access(filename, F_OK))
	{
		if (access(filename, W_OK))
		{
			write(STDERR_FILENO, "Permission denied\n", 19);
			return (-1);
		}
	}
	*fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (*fd == -1)
		return (-1);
	return (0);
}

/**
 * @brief open filename with option, O_WRONLY | O_CREAT | O_APPEND with 0644
 * 
 * @param filename 
 * @return int 
 */
int	open_append(const char *filename, int *fd)
{
	if (access(filename, W_OK))
	{
		write(STDERR_FILENO, "Permission denied\n", 19);
		return (-1);
	}
	*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (-1);
	return (0);
}

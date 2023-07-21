/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:25:17 by dowon             #+#    #+#             */
/*   Updated: 2023/07/26 23:17:09 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "builtins.h"
#include "pipe.h"
#include "redirections.h"

int			close_in(int *fd);
int			close_out(int *fd);
static int	redirection_input(const char *filename, int *fd);
static int	redirection_output(const char *filename, int *fd);
static int	redirection_append(const char *filename, int *fd);

void		set_exit_status(int exit_status);

int			heredoc(const char *filename, int *fd, char *delimiter);

/**
 * @brief open redirections or execute heredoc
 * and set last fd to info.
 * Default : info->in_file = STDIN_FILENO
 * Default : info->out_file = STDOUT_FILENO
 * 
 * @param info 
 * @param redirections 
 */
int	open_redirections(t_exec *info, t_redirections redirections)
{
	info->in_file = STDIN_FILENO;
	info->out_file = STDOUT_FILENO;
	while (*redirections != NULL)
	{
		if ((*redirections)[0][0] == '<' && close_in(&info->in_file) && (
				(ft_strncmp((*redirections)[0], "<", 2) == 0
				&& redirection_input((*redirections)[1], &info->in_file))
				|| (ft_strncmp((*redirections)[0], "<<", 3) == 0
				&& heredoc("/tmp/heredoc", &info->in_file, (*redirections)[1]))
			))
			return (1);
		else if ((*redirections)[0][0] == '>' && close_out(&info->in_file) && (
				(ft_strncmp((*redirections)[0], ">", 2) == 0
				&& redirection_output((*redirections)[1], &info->out_file))
				|| (ft_strncmp((*redirections)[0], ">>", 3) == 0
				&& redirection_append((*redirections)[1], &info->out_file))
			))
			return (1);
		redirections++;
	}
	return (0);
}

/**
 * @brief open filename with option, O_RDONLY
 * 
 * @param filename 
 * @return int 
 */
static int	redirection_input(const char *filename, int *fd)
{
	if (access(filename, F_OK))
	{
		printf("%s: No such file or directory\n", filename);
		return (1);
	}
	if (access(filename, R_OK))
	{
		printf("%s: Permission denied\n", filename);
		return (1);
	}
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		printf("%s: Unknown Error\n", filename);
	return (*fd != -1);
}

/**
 * @brief open filename with option, O_WRONLY | O_CREAT with 0644
 * 
 * @param filename 
 * @return int 
 */
static int	redirection_output(const char *filename, int *fd)
{
	if (access(filename, W_OK))
	{
		set_exit_status(1);
		printf("%s: Permission denied\n", filename);
		return (1);
	}
	*fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (*fd == -1)
	{
		set_exit_status(1);
		printf("%s: Unknown Error\n", filename);
	}
	return (*fd != -1);
}

/**
 * @brief open filename with option, O_WRONLY | O_CREAT | O_APPEND with 0644
 * 
 * @param filename 
 * @return int 
 */
static int	redirection_append(const char *filename, int *fd)
{
	if (*fd != STDOUT_FILENO && close(*fd) == -1)
	{
		set_exit_status(1);
		printf("%s: Failed to close\n", filename);
		return (1);
	}
	if (access(filename, W_OK))
	{
		set_exit_status(1);
		printf("%s: Permission denied\n", filename);
		return (1);
	}
	*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		set_exit_status(1);
		printf("%s: Unknown Error\n", filename);
	}
	return (*fd != -1);
}

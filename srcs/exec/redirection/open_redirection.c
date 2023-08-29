/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:25:17 by dowon             #+#    #+#             */
/*   Updated: 2023/08/29 14:49:58 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "redirection.h"
#include "heredoc/heredoc.h"

static int	handle_input_redirection(char **redirect, int *fd_rd)
{
	if (close_in(fd_rd))
		return (-1);
	if (ft_strncmp(redirect[0], "<", 2) == 0)
	{
		if (open_read(redirect[1], fd_rd))
			return (-1);
	}
	else if (ft_strncmp(redirect[0], "<<", 3) == 0)
	{
		if (heredoc("/tmp/minishell42_heredoc", redirect[1]))
			return (-1);
		*fd_rd = open("/tmp/minishell42_heredoc", O_RDONLY);
		if (*fd_rd == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

static int	handle_output_redirection(char **redirect, int *fd_wr)
{
	if (close_out(fd_wr))
		return (-1);
	if (ft_strncmp(redirect[0], ">", 2) == 0)
	{
		if (open_write(redirect[1], fd_wr))
			return (-1);
	}
	else if (ft_strncmp(redirect[0], ">>", 3) == 0)
	{
		if (open_append(redirect[1], fd_wr))
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	open_redirections(char ***redirect, int *fd_rd, int *fd_wr)
{
	int	idx;

	idx = 0;
	while (redirect[idx] != NULL)
	{
		if (redirect[idx][0][0] == '<')
		{
			if (handle_input_redirection(redirect[idx], fd_rd))
				return (-1);
		}
		else if (redirect[idx][0][0] == '>')
		{
			if (handle_output_redirection(redirect[idx], fd_wr))
				return (-1);
		}
		idx++;
	}
	return (0);
}

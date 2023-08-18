/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:25:17 by dowon             #+#    #+#             */
/*   Updated: 2023/08/18 08:31:32 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libft.h>
#include "redirection.h"
#include "../pipe/pipe.h"

/**
 * @brief success : new fd set to fd_rd, return 0 <>
 * @brief fail : fd set to -1, return -1
 * 
 * @param redirect 
 * @param fd_rd 
 * @return int 
 */
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

/**
 * @brief success : new fd set to fd_rd, return 0 <>
 * @brief fail : fd set to -1, return -1
 * 
 * @param redirect 
 * @param fd_wr 
 * @return int 
 */
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

/**
 * @brief open redirections or execute heredoc
 * and set last fd to info.
 * Default : info->in_file = STDIN_FILENO
 * Default : info->out_file = STDOUT_FILENO
 * 
 * @param info 
 * @param redirections 
 */
int	open_redirections(char ***redirect, int *fd_rd, int *fd_wr)
{
	int idx;

	idx = 0;
	while (redirect[idx] != NULL)
	{
		printf("open_redirections idx : %d\n", idx);
		printf("open_redirections : %p\n", redirect[idx]);
		printf("redirect[idx][0] : %s\n", redirect[idx][0]);
		if (redirect[idx][0][0] == '<')
		{
			printf("redir input\n");
			if (handle_input_redirection(redirect[idx], fd_rd))
				return (-1);
			printf("running\n");
		}
		else if (redirect[idx][0][0] == '>')
		{
			printf("redir output\n");
			if (handle_output_redirection(redirect[idx], fd_wr))
				return (-1);
		}
		else
		{
			printf("[DEBUG MSG] parsing error\n");
			return (-1);
		}
		printf("next\n");
		idx++;
	}
	printf("exit\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:25:17 by dowon             #+#    #+#             */
/*   Updated: 2023/07/21 22:42:07 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <sys/wait.h>
#include "./builtins/builtins.h"
#include "./pipe.h"
#include "./common.h"

static int	open_redirection_input(const char *filename);
static int	open_redirection_output(const char *filename);
static int	open_redirection_output_append(const char *filename);

void	open_redirections(t_exec *info, char **redirections, size_t count)
{
	size_t	idx;

	info->in_file = STDIN_FILENO;
	info->out_file = STDOUT_FILENO;
	idx = 0;
	while (idx < count)
	{
		if (redirections[idx][0] == '<')
			info->in_file = open_redirection_input(redirections[idx] + 1);
		else if (redirections[idx][0] == '>')
		{
			if (redirections[idx][1] == '>')
				info->out_file = open_redirection_output(redirections[idx] + 2);
			else
				info->out_file = open_redirection_output(redirections[idx] + 1);
		}
		++idx;
	}
	if (info->in_file == -1 || info->out_file == -1)
	{
		set_errno(1);
		return ;
	}
	info->pipes[0] = info->in_file;
	info->pipes[2 * info->commands_cnt + 1] = info->out_file;
}

/**
 * @brief open filename with option, O_RDONLY
 * 
 * @param filename 
 * @return int 
 */
static int	open_redirection_input(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		printf("%s : No such file or directory\n", filename);
	return (fd);
}

/**
 * @brief open filename with option, O_WRONLY | O_CREAT with 0644
 * 
 * @param filename 
 * @return int 
 */
static int	open_redirection_output(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		printf("%s : No such file or directory\n", filename);
	return (fd);
}

/**
 * @brief open filename with option, O_WRONLY | O_CREAT | O_APPEND with 0644
 * 
 * @param filename 
 * @return int 
 */
static int	open_redirection_output_append(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		printf("%s : No such file or directory\n", filename);
	return (fd);
}

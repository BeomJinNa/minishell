/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:08:37 by dowon             #+#    #+#             */
/*   Updated: 2023/07/26 23:24:32 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

static char	*remove_last_endl(char *str);
static void	handle_sigint_heredoc(int signal);
static int	execute_heredoc(char *filename, char *delimiter);
void		set_exit_status(int exit_status);

int	heredoc(char *filename, int *fd, char *delimiter)
{
	const pid_t		pid = fork();
	int				exit_status;
	void			(*old_sigint)(int);
	void			(*old_sigquit)(int);

	if (pid == -1)
	{
		set_exit_status(1);
		return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		execute_heredoc(filename, delimiter);
		exit(0);
	}
	old_sigint = signal(SIGINT, SIG_IGN);
	old_sigquit = signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &exit_status, 0);
	printf("Fin\n");
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
	if (WIFEXITED(exit_status))
		set_exit_status(WEXITSTATUS(exit_status));
	return (WEXITSTATUS(exit_status));
}

static void	handle_sigint_heredoc(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

static char	*remove_last_endl(char *str)
{
	char*const	start = str;
	char		*last;

	last = NULL;
	while (*str != '\0')
	{
		if (*str == '\n')
			last = str;
		str++;
	}
	if (last != NULL)
		*last = '\0';
	return (start);
}

static int	execute_heredoc(char *filename, char *delimiter)
{
	const size_t	delimiter_size = ft_strlen(delimiter) + 1;
	char			*line;
	const int		file_fd = open(filename, O_WRONLY | O_CREAT, 0600);

	if (file_fd < 0)
	{
		ft_putstr_fd("Failed to open file.\n", STDOUT_FILENO);
		return (1);
	}
	line = get_next_line(STDIN_FILENO);
	while (line != NULL
		&& ft_strncmp(filename, delimiter, delimiter_size) == 0)
	{
		// TODO : 환경변수 치환해주기
		ft_putstr_fd(line, file_fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(file_fd);
	return (0);
}

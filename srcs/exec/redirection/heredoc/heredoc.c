/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:08:37 by dowon             #+#    #+#             */
/*   Updated: 2023/08/10 16:37:34 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "readline/readline.h"
#include "libft.h"
#include "terminal_parser.h"
#include "heredoc.h"
#include <sys/ioctl.h>
#include <curses.h>
#include <term.h>

static char			*remove_last_endl(char *str);
static void			handle_sigint_heredoc(int signal);
static int			execute_heredoc(char *filename, char *delimiter);
t_heredoc_status	*heredoc_status(void);

void	signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		*heredoc_status() = heredoc_terminate;
		rl_on_new_line();
		rl_replace_line("", 0);
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	}
}

int	heredoc(char *filename, char *delimiter)
{
	sig_t			old_sigint;
	sig_t			old_sigquit;
	int				result;

	old_sigint = signal(SIGINT, signal_handler_heredoc);
	old_sigquit = signal(SIGQUIT, SIG_IGN);
	result = execute_heredoc(filename, delimiter);
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
	return (result);
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
	const size_t	delimiter_len = ft_strlen(delimiter);
	char			*line;
	const int		file_fd = open(filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0600);

	line = NULL;
	if (file_fd < 0)
	{
		ft_putstr_fd("Failed to open file.\n", STDERR_FILENO);
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			printf("\033[1A\033[2C");
		if (line == NULL || *heredoc_status() == heredoc_terminate
			|| ft_strncmp(line, delimiter, delimiter_len + 1) == 0)
			break ;
		ft_putendl_fd(line, file_fd);
		free(line);
	}
	free(line);
	close(file_fd);
	return (*heredoc_status() == heredoc_terminate);
}

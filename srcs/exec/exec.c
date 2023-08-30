/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 22:32:24 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include <sys/wait.h>
#include <hash.h>
#include <terminal_parser.h>
#include "pipe/pipe.h"
#include "builtins/builtins.h"
#include "redirection/heredoc/heredoc.h"
#include <signal.h>
#include <term.h>

int		fork_n_execute(t_command *commands, int *pipes, int idx, int size);
int		run_single_builtin(t_command *commands, int *pipes);
int		fork_n_execute_loop(t_command *commands, int *pipes, int size);
int		heredoc(char *filename, char *delimiter);
void	disable_echoctl(void);
void	enable_echoctl(void);

static void	set_exit_status(int status)
{
	char	*status_str;

	if (status < 0)
		hashtable_addkey("?", "1", get_hashtable(0));
	else
	{
		status_str = ft_itoa(status);
		hashtable_addkey("?", status_str, get_hashtable(0));
		free(status_str);
	}
}

static int	on_execute_fail(sig_t old_sigint, sig_t old_sigquit, int *pipes)
{
	if (pipes != NULL)
		free(pipes);
	set_exit_status(1);
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
	return (-1);
}

static void	sigint_nl(int signo)
{
	if (signo == SIGINT)
		printf("\n");
}

int	execute_commands(t_command *commands, int size)
{
	int*const	pipes = init_pipes(size);
	int			result;
	sig_t		signals[2];

	if (preprocess_heredoc(commands, size))
	{
		set_exit_status(1);
		clean_pipes(pipes, size);
		clean_heredoc();
		return (1);
	}
	signals[0] = signal(SIGINT, sigint_nl);
	signals[1] = signal(SIGQUIT, SIG_IGN);
	enable_echoctl();
	if (pipes == NULL)
		return (on_execute_fail(signals[0], signals[1], pipes));
	if (size == 1 && is_builtin(commands[0].command[0]))
		result = run_single_builtin(commands, pipes);
	else
	{
		result = fork_n_execute_loop(commands, pipes, size);
		if (result < 0)
			return (on_execute_fail(signals[0], signals[1], pipes));
	}
	free(pipes);
	clean_heredoc();
	set_exit_status(result);
	disable_echoctl();
	signal(SIGINT, signals[0]);
	signal(SIGQUIT, signals[1]);
	return (result);
}

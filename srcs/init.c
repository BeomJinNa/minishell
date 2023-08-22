/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:51:52 by dowon             #+#    #+#             */
/*   Updated: 2023/08/22 16:35:02 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "hash.h"

static int	initialize_environment(char **envp);
static int	initialize_terminial(void);
static void	signal_handler(int signo);
int			convert_envp_to_hash(char *row, t_hashtable *hash);

int	initialize_settings(char **envp)
{
	return (
		initialize_terminial()
		|| initialize_environment(envp)
	);
}

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		hashtable_addkey("?", "1", get_hashtable(0));
	}
}

static int	initialize_terminial(void)
{
	struct termios	term;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (tcgetattr(STDIN_FILENO, &term))
		return (-1);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term))
		return (-1);
	return (0);
}

static int	initialize_environment(char **envp)
{
	char			**ptr;
	t_hashtable		*hash;

	hash = get_hashtable(4096);
	if (hash == NULL)
		return (-1);
	if (envp == NULL)
		return (0); ptr = envp;
	while (*ptr != NULL)
	{
		if (convert_envp_to_hash(*ptr++, hash) != 0)
		{
			remove_hashtable(hash);
			return (-1);
		}
	}
	hashtable_addkey("?", "0", hash);
	return (0);
}

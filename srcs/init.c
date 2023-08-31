/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:51:52 by dowon             #+#    #+#             */
/*   Updated: 2023/08/31 17:19:48 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "hash.h"

static int	initialize_environment(char **envp);
static int	initialize_terminial(void);
static void	signal_handler(int signo);
int			convert_envp_to_hash(char *row, t_hashtable *hash);
void		disable_echoctl(void);
int			add_shlvl(t_hashtable *hash);

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
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	disable_echoctl();
	return (0);
}

static void	set_secret_envs(void)
{
	char*const			directory = getcwd(NULL, 0);
	t_hashtable*const	hash = get_hashtable(0);

	hashtable_addkey("?", "0", hash);
	hashtable_removekey("OLDPWD", hash);
	hashtable_addkey("?heredoc_cnt", "0", hash);
	if (directory == NULL)
	{
		if (hashtable_get("PWD", hash) == NULL)
			hashtable_addkey("?pwd", "", hash);
		else
			hashtable_addkey("?pwd", hashtable_get("PWD", hash), hash);
	}
	else
	{
		hashtable_addkey("?pwd", directory, hash);
		free(directory);
	}
}

static int	initialize_environment(char **envp)
{
	char			**ptr;
	t_hashtable		*hash;

	hash = get_hashtable(4096);
	if (hash == NULL)
		return (-1);
	if (envp == NULL)
		return (0);
	ptr = envp;
	while (*ptr != NULL)
	{
		if (convert_envp_to_hash(*ptr++, hash) != 0)
		{
			remove_hashtable(hash);
			return (-1);
		}
	}
	set_secret_envs();
	add_shlvl(hash);
	return (0);
}

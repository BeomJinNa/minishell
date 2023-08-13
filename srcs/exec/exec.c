/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/08/13 18:35:34 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include <hash.h>
#include <terminal_parser.h>
#include "pipe/pipe.h"
#include "builtins/builtins.h"
#include "redirection/redirection.h"

void	exec_command(char **command)
{
	char	*exec_path;
	if (ft_strncmp(command[0], "echo", 5) == 0)
		exit(builtin_echo(command + 1));
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		exit(builtin_cd(command + 1));
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		exit(builtin_pwd(command + 1));
	else if (ft_strncmp(command[0], "export", 6) == 0)
		exit(builtin_export(command + 1));
	else if (ft_strncmp(command[0], "unset", 5) == 0)
		exit(builtin_unset(command + 1));
	else if (ft_strncmp(command[0], "env", 4) == 0)
		exit(builtin_env(command + 1));
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		exit(builtin_exit(command + 1));
	exec_path = get_excutable_path("/Users/dowon/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:~/.dotnet/tools:/Library/Apple/usr/bin:/Users/dowon/.brew/bin:/Users/dowon/Library/Python/3.8/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Users/dowon/Library/Python/3.8/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin", command[0]);
	if (exec_path == NULL)
	{
		printf("%s : command not found\n", command[0]);
		exit(127);
	}
	execve(exec_path,
		command, NULL);
}

int	execute_child(t_command command, int *pipes, int idx)
{
	printf("exec_child\n");
	if (open_redirections(command.redirections,
			readpipe_at(pipes, idx), writepipe_at(pipes, idx + 1)))
		return (-1);
	printf("redirections_opened\n");
	if (dup_pipes(pipes, idx))
		return (-1);
	printf("pipes_duplicated\n");
	exec_command(command.command);
	close_rw_pipes(pipes, idx);
	return (-1);
}

int	fork_n_execute(t_command *commands, int *pipes, int idx, int size)
{
	const pid_t	fork_pid = fork();

	if (fork_pid == -1)
		return (-1);
	if (fork_pid == 0)
	{
		printf("child : %d\n", getpid());
		if (execute_child(commands[idx], pipes, idx))
		{
			clean_pipes(pipes, size);
			return (-1);
		}
	}
	else if (close_rw_pipes(pipes, idx))
	{
		clean_pipes(pipes, size);
		return (-1);
	}
	return (0);
}

static int	wait_all(int size)
{
	int		idx;
	int		status;
	char	*status_str;

	idx = 0;
	while (idx < size)
	{
		wait(&status);
		++idx;
		if (WIFEXITED(status))
		{
			status_str = ft_itoa(WEXITSTATUS(status));
			if (status_str == NULL)
				return (-1);
			if (hashtable_addkey("?", status_str, get_hashtable(0)))
				return (-1);
		}
	}
	return (0);
}

int	execute_commands(t_command *commands, int size)
{
	int*const	pipes = init_pipes(size);
	int			idx;

	if (pipes == NULL)
		return (-1);
	idx = 0;
	while (idx < size)
	{
		if (fork_n_execute(commands, pipes, idx, size))
			return (-1);
		idx++;
	}
	return (wait_all(size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:30:56 by dowon             #+#    #+#             */
/*   Updated: 2023/07/25 21:42:42 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include "builtins.h"
#include "pipe.h"
#include "exec.h"

void	open_redirections(t_exec *info, char **redirections, size_t count);
int		readpipe_at(int *pipes, int idx);
int		writepipe_at(int *pipes, int idx);

void	execute_command(t_command command)
{
	if (ft_strncmp(command[0], "echo", 4))
		exit(builtin_echo(command + 1));
	else if (ft_strncmp(command[0], "cd", 2))
		exit(builtin_cd(command + 1));
	else if (ft_strncmp(command[0], "pwd", 3))
		exit(builtin_pwd(command + 1));
	else if (ft_strncmp(command[0], "export", 5))
		exit(builtin_export(command + 1));
	else if (ft_strncmp(command[0], "unset", 5))
		exit(builtin_unset(command + 1));
	else if (ft_strncmp(command[0], "env", 3))
		exit(builtin_env(command + 1));
	else if (ft_strncmp(command[0], "exit", 4))
		exit(builtin_exit(command + 1));
	else
		execve(get_excutable_path(get_env("PATH"), command[0]),
			command, get_all_env());
}

void	execute_commands(t_exec *info)
{
	size_t	idx;
	pid_t	fork_pid;
	char	**args;

	idx = 0;
	while (info->commands[idx] != NULL)
	{
		fork_pid = fork();
		if (fork_pid == 0)
		{
			if (idx != 0)
				close(writepipe_at(info->pipes, idx));
			if (readpipe_at(info->pipes, idx) != STDIN_FILENO)
			{
				dup2(readpipe_at(info->pipes, idx), STDIN_FILENO);
				close(readpipe_at(info->pipes, idx));
			}
			if (info->commands[idx + 1] != NULL)
				close(readpipe_at(info->pipes, idx + 1));
			if (writepipe_at(info->pipes, idx + 1) != STDOUT_FILENO)
			{
				dup2(writepipe_at(info->pipes, idx + 1), STDOUT_FILENO);
				close(writepipe_at(info->pipes, idx + 1));
			}
			execute_command(info->commands[idx]);
			printf("Execvp failed.\n");
		}
		else
		{
			if (readpipe_at(info->pipes, idx) != STDIN_FILENO)
				close(readpipe_at(info->pipes, idx));
			if (writepipe_at(info->pipes, idx + 1) != STDOUT_FILENO)
				close(writepipe_at(info->pipes, idx + 1));
		}
		++idx;
	}
	idx = 0;
	while (info->commands[idx] != NULL)
	{
		wait(NULL);
		++idx;
	}
}

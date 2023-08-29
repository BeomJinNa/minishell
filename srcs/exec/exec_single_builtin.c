/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:29:44 by dowon             #+#    #+#             */
/*   Updated: 2023/08/29 16:26:44 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "terminal_parser.h"
#include "redirection/redirection.h"
#include "pipe/pipe.h"
#include "builtins/builtins.h"

int	run_single_builtin(t_command *commands, int *pipes)
{
	const int	in = dup(STDOUT_FILENO);
	const int	out = dup(STDIN_FILENO);
	int			result;

	if (open_redirections(commands[0].redirections,
			readpipe_at(pipes, 0), writepipe_at(pipes, 1)))
		return (1);
	if (dup_pipes(pipes, 0))
		return (1);
	result = run_builtin(commands[0].command);
	close_rw_pipes(pipes, 0);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	return (result);
}

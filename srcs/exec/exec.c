/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:23:29 by dowon             #+#    #+#             */
/*   Updated: 2023/07/25 21:37:01 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "pipe.h"

static size_t	count_nullterminated(void **commands);

void	exec(t_redirections redirections, t_commands commands)
{
	t_exec			exec_info;

	exec_info.pipes = init_pipes(count_nullterminated(commands));
	if (exec_info.pipes == NULL)
	{
		set_errno(1);
		return ;
	}	
	exec_info.commands = commands;
	if (open_redirections(&exec_info, redirections))
		return ;
	execute_commands(&exec_info);
	free(exec_info.pipes);
}

static size_t	count_nullterminated(void **commands)
{
	void**const	start = commands;

	while (*commands != NULL)
		++commands;
	return (commands - start);
}

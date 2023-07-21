/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:27:01 by dowon             #+#    #+#             */
/*   Updated: 2023/07/21 22:39:10 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

typedef enum e_pipe_fd
{
	pipe_fd_read = 0,
	pipe_fd_write = 1,
}	t_pipe_fd;

typedef char**	t_command;
typedef struct s_exec {
	int				in_file;
	int				out_file;
	int				*pipes;
	t_command		*commands;
	size_t			commands_cnt;
}	t_exec;

int	*init_pipes(size_t process_count);

#endif
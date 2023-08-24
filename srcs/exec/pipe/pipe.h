/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:56:07 by dowon             #+#    #+#             */
/*   Updated: 2023/08/24 21:20:03 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include <stddef.h>

typedef enum e_pipe_fd
{
	pipe_read = 0,
	pipe_write = 1,
}	t_pipe_fd;

typedef struct s_exec {
	int			*pipes;
	char		**commands;
	size_t		commands_cnt;
}	t_exec;

int		dup_pipes(int *pipes, int idx);
int		*readpipe_at(int *pipes, int idx);
int		*writepipe_at(int *pipes, int idx);
int		*init_pipes(int process_count);
void	clean_pipes(int *pipes, int process_count);
int		close_rw_pipes(int *pipes, int idx);
char	*get_excutable_path(char *path, char *command);

#endif

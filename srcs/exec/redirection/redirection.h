/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:26:58 by dowon             #+#    #+#             */
/*   Updated: 2023/08/11 04:44:25 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H
# include "heredoc/heredoc.h"

int	close_in(int *fd);
int	close_out(int *fd);
int	open_read(const char *filename, int *fd);
int	open_write(const char *filename, int *fd);
int	open_append(const char *filename, int *fd);
int	open_redirections(char ***redirect, int *fd_rd, int *fd_wr);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 02:13:31 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 16:41:27 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "terminal_parser.h"

typedef enum e_heredoc_status
{
	heredoc_ok,
	heredoc_terminate,
}	t_heredoc_status;

typedef struct s_heredoc
{
	t_heredoc_status	status;
}	t_heredoc;

t_heredoc_status	*heredoc_status(void);
int					heredoc(char *filename, char *delimiter);
int					preprocess_heredoc(t_command *commands, int size);
void				clean_heredoc(void);

#endif
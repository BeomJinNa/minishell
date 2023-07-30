/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 02:13:31 by dowon             #+#    #+#             */
/*   Updated: 2023/08/07 02:23:18 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef enum e_heredoc_status
{
	heredoc_continue,
	heredoc_terminate,
}	t_heredoc_status;

typedef struct s_heredoc
{
	t_heredoc_status	status;
}	t_heredoc;

#endif
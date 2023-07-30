/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 02:12:51 by dowon             #+#    #+#             */
/*   Updated: 2023/08/08 23:02:00 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

t_heredoc_status	*heredoc_status(void)
{
	static t_heredoc_status	status;

	return (&status);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:38:47 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 16:39:47 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include "libft.h"
#include "hash.h"

int	heredoc_cnt_get(void)
{
	return (ft_atoi(hashtable_get("?heredoc_cnt", get_hashtable(0))));
}

void	heredoc_cnt_increase(void)
{
	char	*cnt_str;

	cnt_str = ft_itoa(heredoc_cnt_get() + 1);
	hashtable_addkey("?heredoc_cnt", cnt_str, get_hashtable(0));
	free(cnt_str);
}

void	heredoc_cnt_decrease(void)
{
	char	*cnt_str;

	cnt_str = ft_itoa(heredoc_cnt_get() - 1);
	hashtable_addkey("?heredoc_cnt", cnt_str, get_hashtable(0));
	free(cnt_str);
}

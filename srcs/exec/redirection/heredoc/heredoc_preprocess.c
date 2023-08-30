/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:56:59 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 22:52:03 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/file.h>
#include "libft.h"
#include "heredoc.h"
#include "hash.h"

void	heredoc_cnt_increase(void);
void	heredoc_cnt_decrease(void);
int		heredoc_cnt_get(void);

static char	*generate_heredoc_filename(void)
{
	char	*filename;
	char	*num_str;
	int		idx;

	idx = 0;
	num_str = ft_itoa(idx);
	filename = ft_strjoin("/tmp/42_heredoc_", num_str);
	free(num_str);
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		num_str = ft_itoa(idx);
		filename = ft_strjoin("/tmp/42_heredoc_", num_str);
		free(num_str);
		++idx;
	}
	return (filename);
}

static void	heredoc_filename_add(char *filename)
{
	char		*cnt_str;
	char		*key;

	cnt_str = ft_itoa(heredoc_cnt_get());
	key = ft_strjoin("?heredoc_file_", cnt_str);
	free(cnt_str);
	hashtable_addkey(key, filename, get_hashtable(0));
	free(key);
	heredoc_cnt_increase();
}

void	clean_heredoc(void)
{
	const int	total_cnt = heredoc_cnt_get();
	int			idx;
	char		*cnt_str;
	char		*key;

	idx = 0;
	while (idx < total_cnt)
	{
		cnt_str = ft_itoa(idx);
		key = ft_strjoin("?heredoc_file_", cnt_str);
		free(cnt_str);
		unlink(hashtable_get(key, get_hashtable(0)));
		hashtable_removekey(key, get_hashtable(0));
		free(key);
		heredoc_cnt_decrease();
		idx++;
	}
}

static int	preprocess(char **redir)
{
	char*const	filename = generate_heredoc_filename();

	if (heredoc(filename, redir[1]))
	{
		unlink(filename);
		free(filename);
		return (-1);
	}
	free(redir[0]);
	redir[0] = ft_strdup("<");
	free(redir[1]);
	redir[1] = filename;
	heredoc_filename_add(filename);
	return (0);
}

int	preprocess_heredoc(t_command *commands, int size)
{
	int		idx;
	char	***redir;

	idx = 0;
	while (idx < size)
	{
		redir = commands[idx].redirections;
		while (*redir != NULL)
		{
			if (ft_strncmp((*redir)[0], "<<", 3) == 0)
			{
				if (preprocess(*redir))
					return (-1);
			}
			++redir;
		}
		++idx;
	}
	return (0);
}

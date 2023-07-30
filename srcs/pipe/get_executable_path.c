/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:43:54 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 16:14:49 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static char	*remove_matrix(char **matrix);
static char	*get_joined_path(char *str, char *suffix);
static int	check_current_path_available(char **buffer, char *command);

char	*get_excutable_path(char *path, char *command)
{
	char	**path_arr;
	char	**ptr;
	char	*output;

	if (check_current_path_available(&output, command))
		return (output);
	path_arr = ft_split(path, ':');
	if (path_arr == NULL)
		return (NULL);
	ptr = path_arr;
	while (*ptr != NULL)
	{
		output = get_joined_path(*ptr, command);
		if (output == NULL)
			return (remove_matrix(path_arr));
		if (access(output, F_OK | X_OK) == 0)
		{
			remove_matrix(path_arr);
			return (output);
		}
		free(output);
		ptr++;
	}
	return (remove_matrix(path_arr));
}

static char	*remove_matrix(char **matrix)
{
	char	**ptr;

	ptr = matrix;
	if (ptr != NULL)
	{
		while (*ptr != NULL)
		{
			free(*ptr);
			ptr++;
		}
		free(matrix);
	}
	return (NULL);
}

static char	*get_joined_path(char *str, char *suffix)
{
	char	*output;
	char	*temp;

	temp = NULL;
	if (str[ft_strlen(str) - 1] != '/')
	{
		temp = ft_strjoin(str, "/");
		if (temp == NULL)
			return (NULL);
		output = ft_strjoin(temp, suffix);
	}
	else
		output = ft_strjoin(str, suffix);
	if (temp != NULL)
		free (temp);
	return (output);
}

static int	check_current_path_available(char **buffer, char *command)
{
	if (buffer == NULL)
		return (0);
	*buffer = get_joined_path("./", command);
	if (*buffer != NULL && access(*buffer, F_OK | X_OK) == 0)
		return (1);
	if (*buffer != NULL)
		free(*buffer);
	*buffer = NULL;
	return (0);
}

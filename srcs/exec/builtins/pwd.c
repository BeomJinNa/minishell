/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:48:57 by dowon             #+#    #+#             */
/*   Updated: 2023/08/30 22:05:39 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hash.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>

int	builtin_pwd(char **args)
{
	char	*buffer;

	(void)args;
	buffer = getcwd(NULL, 0);
	if (errno && errno != ENOENT)
	{
		if (buffer != NULL)
			free(buffer);
		return (1);
	}
	if (buffer != NULL)
		free(buffer);
	printf("%s\n", hashtable_get("?pwd", get_hashtable(0)));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:48:57 by dowon             #+#    #+#             */
/*   Updated: 2023/08/18 12:51:46 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdio.h>

int	builtin_pwd(char **args)
{
	char*const	buffer = getcwd(NULL, 0);

	(void)args;
	if (buffer == NULL)
		return (1);
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}

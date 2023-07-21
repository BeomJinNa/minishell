/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:48:57 by dowon             #+#    #+#             */
/*   Updated: 2023/07/21 22:56:58 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

int	builtin_pwd(char **args)
{
	const char*const	buffer = getcwd(NULL, 0);

	ft_putstr_fd(buffer, STDOUT_FILENO);
	free(buffer);
	return (0);
}

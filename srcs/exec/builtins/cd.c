/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:43:42 by dowon             #+#    #+#             */
/*   Updated: 2023/08/31 18:31:02 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "builtins.h"
#include "hash.h"

static void	set_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		hashtable_addkey("?pwd", pwd, get_hashtable(0));
		hashtable_addkey("PWD", pwd, get_hashtable(0));
		free(pwd);
	}
}

int	builtin_cd(char **args)
{
	const size_t	argc = count_args(args);

	if (argc == 0)
	{
		printf("cd without arguments are not supported\n");
		return (1);
	}
	if (chdir(args[0]) == -1)
	{
		printf("%s: No such file or directory\n", args[0]);
		return (1);
	}
	hashtable_addkey("OLDPWD",
		hashtable_get("?pwd", get_hashtable(0)), get_hashtable(0));
	set_pwd();
	return (0);
}

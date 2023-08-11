/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:51:09 by dowon             #+#    #+#             */
/*   Updated: 2023/08/11 04:09:01 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "hashtable_ext.h"
#include "builtins.h"

int	builtin_env(char **args)
{
	t_hashtable*const	hash = get_hashtable(0);
	const size_t		argc = count_args(args);

	if (hash == NULL)
		return (1);
	if (argc == 0)
	{
		print_hashtable(hash, "");
		return (0);
	}
	else
		printf("env: too many arguments\n");
	return (1);
}

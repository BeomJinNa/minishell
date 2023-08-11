/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 02:36:00 by dowon             #+#    #+#             */
/*   Updated: 2023/08/11 04:30:48 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashtable_ext.h"

static int	export_variable(char *str)
{
	char*const	divider = ft_strchr(str, '=');
	t_hashtable*const	hash = get_hashtable(0);

	if (hash == NULL)
		return (1);
	if (divider == NULL)
		return (0);
	*divider = '\0';
	if (check_valid_identifier(str))
	{
		printf("export: `%s`: not a valid identifier");
		return (1);
	}
	if (hashtable_addkey(str, divider + 1, hash))
		return (1);
	return (0);
}

/**
 * @brief builtin_export
 * 
 * @param args 
 * @return int 
 */
int	builtin_export(char **args)
{
	const size_t		argc = count_args(args);
	t_hashtable*const	hash = get_hashtable(0);
	size_t				idx;
	int					result;

	if (hash == NULL)
		return (1);
	if (argc == 0)
	{
		print_hashtable(hash, "declare -x ");
		return (0);
	}
	result = 0;
	idx = 0;
	while (idx < argc)
	{
		result |= export_variable(args[idx]);
		++idx;
	}
	return (result);
}

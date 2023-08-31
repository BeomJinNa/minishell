/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:08:38 by bena              #+#    #+#             */
/*   Updated: 2023/08/31 17:18:44 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hash.h"

int	is_str_int_format(const char *str);

int	add_shlvl(t_hashtable *hash)
{
	char	*shlvl_str;
	int		shlvl;

	if (hash == NULL)
		return (1);
	shlvl_str = hashtable_get("SHLVL", hash);
	if (is_str_int_format(shlvl_str))
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
		if (shlvl < 0 || shlvl > 999)
		{
			shlvl = 0;
		}
		shlvl_str = ft_itoa(shlvl);
		hashtable_addkey("SHLVL", shlvl_str, hash);
		free(shlvl_str);
		return (0);
	}
	hashtable_addkey("SHLVL", "1", hash);
	return (0);
}

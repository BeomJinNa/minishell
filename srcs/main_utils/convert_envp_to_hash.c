/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envp_to_hash.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:07:35 by bena              #+#    #+#             */
/*   Updated: 2023/08/20 18:12:38 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "hash.h"

int	convert_envp_to_hash(char *row, t_hashtable *hash)
{
	char	*ptr;

	if (row == NULL)
		return (-1);
	ptr = row;
	while (*ptr && *ptr != '=')
		ptr++;
	*ptr++ = '\0';
	return (hashtable_addkey(row, ptr, hash));
}

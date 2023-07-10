/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hashtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:15:08 by bena              #+#    #+#             */
/*   Updated: 2023/07/11 12:38:05 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

t_hashtable	*init_hashtable(unsigned int size)
{
	t_hashtable		*new_hashtable;
	t_hashnode		**table;
	unsigned int	index;

	new_hashtable = (t_hashtable *)malloc(sizeof(t_hashtable));
	if (new_hashtable == NULL)
		return (NULL);
	new_hashtable->size = size;
	table = (t_hashnode **)malloc(sizeof(t_hashnode *) * size);
	if (table == NULL)
	{
		free(new_hashtable);
		return (NULL);
	}
	index = 0;
	while (index < size)
	{
		table[index] = NULL;
		index++;
	}
	return (new_hashtable);
}

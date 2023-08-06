/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hashtable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:21:40 by bena              #+#    #+#             */
/*   Updated: 2023/08/07 05:22:25 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hashtable	*get_hashtable(unsigned int init)
{
	static t_hashtable	*hash = (void *)0;

	if (init == 0)
		return (hash);
	hash = init_hashtable(init);
	return (hash);
}

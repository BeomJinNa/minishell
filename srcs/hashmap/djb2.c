/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djb2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:33:50 by bena              #+#    #+#             */
/*   Updated: 2023/07/10 08:08:36 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

unsigned int	djb2(const char *str, unsigned int bucket_size)
{
	const unsigned char	*ptr;
	unsigned int		output;

	if (str == (void *)0)
		return (0);
	ptr = (const unsigned char *)str;
	output = 5381;
	while (*ptr)
	{
		output = ((output << 5) + output) + (unsigned int)(*ptr);
		ptr++;
	}
	return (output % bucket_size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:31:33 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 14:09:03 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*hash_memset(void *b, int c, unsigned int len)
{
	unsigned char	*address;
	unsigned char	value;

	value = (unsigned char)c;
	address = (unsigned char *)b;
	while (len--)
		*address++ = value;
	return (b);
}

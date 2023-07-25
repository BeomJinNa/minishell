/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 20:18:44 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 14:26:13 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			*hash_memset(void *b, int c, unsigned int len);
static size_t	hash_strlen(const char *s);
static size_t	hash_strlcpy(char *dest, const char *src, size_t size);
static void		*hash_memcpy(void *dst, const void *src, size_t n);

char	*hash_strdup(const char *s1)
{
	char	*dest;
	size_t	size;

	size = hash_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == 0)
		return (0);
	hash_strlcpy(dest, s1, size + 1);
	return (dest);
}

static size_t	hash_strlcpy(char *dest, const char *src, size_t size)
{
	size_t			src_size;

	src_size = hash_strlen(src);
	if (size == 0)
		return (src_size);
	if (size > src_size + 1)
		size = src_size + 1;
	hash_memcpy(dest, src, size - 1);
	*(dest + size - 1) = 0;
	return (src_size);
}

static size_t	hash_strlen(const char *s)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
		ptr++;
	return (ptr - s);
}

static void	*hash_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*address_src;
	unsigned char	*address_dst;

	if (dst == 0 && src == 0)
		return (0);
	address_src = (unsigned char *)src;
	address_dst = (unsigned char *)dst;
	while (n--)
		*address_dst++ = *address_src++;
	return (dst);
}

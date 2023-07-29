/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 20:18:44 by bena              #+#    #+#             */
/*   Updated: 2023/07/27 22:35:05 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	variable_strnlen(const char *s, size_t max_len);
static size_t	variable_strlcpy(char *dest, const char *src, size_t size);
static void		*variable_memcpy(void *dst, const void *src, size_t n);

char	*va_strndup(const char *str, size_t max_len)
{
	char	*dest;
	size_t	size;

	size = variable_strnlen(str, max_len);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == 0)
		return (0);
	variable_strlcpy(dest, str, size + 1);
	return (dest);
}

static size_t	variable_strlcpy(char *dest, const char *src, size_t size)
{
	size_t			src_size;

	src_size = variable_strnlen(src, size);
	if (size == 0)
		return (src_size);
	if (size > src_size + 1)
		size = src_size + 1;
	variable_memcpy(dest, src, size - 1);
	*(dest + size - 1) = 0;
	return (src_size);
}

static size_t	variable_strnlen(const char *s, size_t max_len)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr && max_len > 0)
	{
		ptr++;
		max_len--;
	}
	return (ptr - s);
}

static void	*variable_memcpy(void *dst, const void *src, size_t n)
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

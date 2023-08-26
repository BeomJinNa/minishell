/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 02:36:34 by bena              #+#    #+#             */
/*   Updated: 2023/08/26 20:43:13 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	finish_sort(void *start, int elem_byte, int size,
				int cmp(void *, void *));
static void	swap(void *a, void *b, int elem_byte, void **pivot_ptr);
static void	*select_pivot(void *start, int elem_byte, int size,
				int cmp(void *, void *));

void	sort_memory(void *start, int elem_byte, int size,
		int cmp(void *, void *))
{
	void *const	end = (void *const)((char *)start + (size - 1) * elem_byte);
	void		*pivot;
	void		*left;
	void		*right;

	if (size < 4)
		return (finish_sort(start, elem_byte, size, cmp));
	pivot = select_pivot(start, elem_byte, size, cmp);
	left = start;
	right = end;
	while (left < right)
	{
		while (left < end && cmp(left, pivot) < 0)
			left = (void *)((char *)left + elem_byte);
		while (right > start && cmp(right, pivot) >= 0)
			right = (void *)((char *)right - elem_byte);
		if (left < right)
			swap(left, right, elem_byte, &pivot);
	}
	if (left == right)
		left = (void *)((char *)left + elem_byte);
	sort_memory(start, elem_byte,
		(int)((char *)right - (char *)start) / elem_byte + 1, cmp);
	sort_memory(left, elem_byte,
		(int)((char *)end - (char *)left) / elem_byte + 1, cmp);
}

static void	finish_sort(void *start, int elem_byte, int size,
		int cmp(void *, void *))
{
	void *const	end = (void *)((char *)start + (size - 1) * elem_byte);

	if (size == 1)
		return ;
	if (size == 2)
	{
		if (cmp(start, end) > 0)
			return (swap(start, end, elem_byte, NULL));
		else
			return ;
	}
	if (cmp(start, (void *)((char *)start + elem_byte)) > 0)
		swap(start, (void *)((char *)start + elem_byte), elem_byte, NULL);
	if (cmp(start, (void *)((char *)start + elem_byte * 2)) > 0)
		swap(start, (void *)((char *)start + elem_byte * 2), elem_byte, NULL);
	if (cmp((void *)((char *)start + elem_byte),
		(void *)((char *)start + elem_byte * 2)) > 0)
		swap((void *)((char *)start + elem_byte),
			(void *)((char *)start + elem_byte * 2), elem_byte, NULL);
}

static void	swap(void *a, void *b, int elem_byte, void **pivot_ptr)
{
	char	temp;
	int		i;

	i = 0;
	while (i < elem_byte)
	{
		temp = *((char *)a + i);
		*((char *)a + i) = *((char *)b + i);
		*((char *)b + i) = temp;
		i++;
	}
	if (pivot_ptr != NULL)
	{
		if (*pivot_ptr == a)
			*pivot_ptr = b;
		else if (*pivot_ptr == b)
			*pivot_ptr = a;
	}
}

static void	*select_pivot(void *start, int elem_byte, int size,
		int cmp(void *, void *))
{
	void	*temp[3];

	temp[0] = start;
	temp[1] = (void *)((char *)start + (size / 2) * elem_byte);
	temp[2] = (void *)((char *)start + (size - 1) * elem_byte);
	if (cmp(temp[0], temp[1]) > 0)
		swap(temp[0], temp[1], elem_byte, NULL);
	if (cmp(temp[0], temp[2]) > 0)
		swap(temp[0], temp[2], elem_byte, NULL);
	if (cmp(temp[1], temp[2]) > 0)
		swap(temp[1], temp[2], elem_byte, NULL);
	return (temp[1]);
}

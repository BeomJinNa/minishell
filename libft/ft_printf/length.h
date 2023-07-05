/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:05:16 by bena              #+#    #+#             */
/*   Updated: 2023/04/29 04:43:42 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LENGTH_H
# define LENGTH_H

typedef struct s_length
{
	size_t	space;
	size_t	total;
	size_t	value;
	size_t	number;
	size_t	precision_padding;
}			t_length;
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_brace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:49:12 by bena              #+#    #+#             */
/*   Updated: 2023/07/24 11:23:20 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brace.h"

void	init_brace(t_brace *brace, char *str)
{
	brace->in_brace = 0;
	brace->in_double_brace = 0;
	brace->on_redirection = 0;
	brace->count = 0;
	brace->ptr = str;
}

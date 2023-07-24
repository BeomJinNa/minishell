/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:27:53 by bena              #+#    #+#             */
/*   Updated: 2023/07/24 13:25:20 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRACE_H
# define BRACE_H

typedef struct brace
{
	int		in_brace;
	int		in_double_brace;
	int		on_redirection;
	int		count;
	char	*ptr;
}			t_brace;

void	init_brace(t_brace *brace, char *str);
#endif

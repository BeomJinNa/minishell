/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_alloc_errors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 04:52:29 by bena              #+#    #+#             */
/*   Updated: 2023/08/24 16:06:20 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_ALLOC_ERRORS_H
# define E_ALLOC_ERRORS_H

enum e_alloc_errors
{
	M_SUCCESS = 0,
	M_MALLOC_FAIL = -1,
	M_SYNTAX_ERROR_REDIRECTIONS = -2,
	M_SYNTAX_ERROR_ENV_VARIABLES = -3,
	M_SYNTAX_ERROR_PIPE = -4
};
#endif

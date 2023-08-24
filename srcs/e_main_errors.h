/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_main_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 06:40:06 by bena              #+#    #+#             */
/*   Updated: 2023/08/24 16:07:48 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_MAIN_ERRORS_H
# define E_MAIN_ERRORS_H

enum e_main_errors
{
	M_MODULE_PARSER = 1,
	M_MODULE_PIPE = 2,
	M_CALL_PERROR = -2,
	M_ERROR_MALLOC_FAIL = -100,
	M_ERROR_SYNTAX_REDIRECTION = -101,
	M_ERROR_SYNTAX_ENV_VARIABLE = -102,
	M_ERROR_SYNTAX_QUOTE = -103,
	M_ERROR_SYNTAX_PIPE = -104
};
#endif

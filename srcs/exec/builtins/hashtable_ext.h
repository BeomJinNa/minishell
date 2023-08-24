/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_ext.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 03:55:19 by dowon             #+#    #+#             */
/*   Updated: 2023/08/24 14:53:46 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_EXT_H
# define HASHTABLE_EXT_H
# include "hash.h"

void	print_hashtable(t_hashtable *hash, const char *prefix,
			const char *wrapper, int include_null);

#endif
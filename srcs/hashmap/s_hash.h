/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hash.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:33:46 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 14:34:23 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_HASH_H
# define S_HASH_H

typedef struct s_hashnode	t_hashnode;
typedef struct s_hashtable	t_hashtable;

struct s_hashnode
{
	char		*key;
	char		*value;
	t_hashnode	*next;
};

struct s_hashtable
{
	unsigned int	size;
	t_hashnode		**table;
};
#endif

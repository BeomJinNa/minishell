/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:36:09 by bena              #+#    #+#             */
/*   Updated: 2023/07/25 14:04:00 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

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

t_hashtable		*init_hashtable(unsigned int size);
t_hashtable		*extend_hashtable(t_hashtable *hash, unsigned int size);
void			remove_hashtable(t_hashtable *hash);
char			*hashtable_get(char *key, t_hashtable *hash);
int				hashtable_addkey(char *key, char *value, t_hashtable *hash);
void			hashtable_removekey(char *key, t_hashtable *hash);
unsigned int	djb2(const char *str, unsigned int bucket_size);
#endif

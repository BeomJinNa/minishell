/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:38:43 by bena              #+#    #+#             */
/*   Updated: 2023/08/23 20:55:59 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	compare_token(void *a, void *b)
{
	unsigned char	*token_a;
	unsigned char	*token_b;

	token_a = *(unsigned char **)a;
	token_b = *(unsigned char **)b;
	while (*token_a || *token_b)
	{
		if (*token_a != *token_b)
			return (*token_a - *token_b);
		token_a++;
		token_b++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:27:58 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 17:43:34 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_token_size(char *str);
static void	merge_strings(char *buffer, char **tokens);

char	*merge_tokens(char **tokens)
{
	int		size;
	char	**ptr;
	char	*output;

	if (tokens == NULL)
		return (NULL);
	size = 0;
	ptr = tokens;
	while (*ptr != NULL)
		size += get_token_size(*ptr++);
	output = (char *)malloc(sizeof(char) * (size + 1));
	if (output == NULL)
		return (NULL);
	merge_strings(output, tokens);
	return (output);
}

static int	get_token_size(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

static void	merge_strings(char *buffer, char **tokens)
{
	char	*ptr;

	while (*tokens != NULL)
	{
		ptr = *tokens;
		while (*ptr)
			*buffer++ = *ptr++;
		tokens++;
	}
	*buffer = '\0';
}

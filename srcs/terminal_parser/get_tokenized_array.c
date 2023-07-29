/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokenized_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bena <bena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:41:12 by bena              #+#    #+#             */
/*   Updated: 2023/07/29 19:12:12 by bena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			get_number_of_tokens(const char *str, char c);
static char	*get_next_token(const char **str, char c);
static int	push_to_the_next_token(const char **str, char c);
static char	**remove_matrix(char **array);

char	**get_tokenized_array(const char *str, char c)
{
	int		size;
	char	**output;
	int		i;

	if (str == NULL)
		return (NULL);
	size = get_number_of_tokens(str, c);
	if (size < 0)
		return (NULL);
	output = (char **)malloc(sizeof(char *) * (size + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		output[i] = get_next_token(&str, c);
		if (output[i] == NULL)
			return (remove_matrix(output));
		i++;
	}
	output[size] = NULL;
	return (output);
}

int	get_number_of_tokens(const char *str, char c)
{
	int	output;
	int	token_size;

	output = 0;
	while (*str)
	{
		token_size = push_to_the_next_token(&str, c);
		if (token_size > 0)
			output++;
		str += token_size;
		if (token_size < 0)
			return (-1);
	}
	return (output);
}

static char	*get_next_token(const char **str, char c)
{
	char	*output;
	int		token_size;
	int		i;

	if (str == NULL || *str == NULL)
		return (NULL);
	token_size = push_to_the_next_token(str, c);
	output = (char *)malloc(sizeof(char) * (token_size + 1));
	if (output == NULL)
		return (NULL);
	i = -1;
	while (++i < token_size)
		output[i] = (*str)[i];
	output[token_size] = '\0';
	*str += token_size;
	return (output);
}

static int	push_to_the_next_token(const char **str, char c)
{
	const char	*ptr;
	int			in_brace;
	int			in_double_brace;

	if (str == NULL || *str == NULL)
		return (0);
	in_brace = 0;
	in_double_brace = 0;
	while (**str && **str == c)
		(*str)++;
	ptr = *str;
	while (*ptr)
	{
		if (*ptr == '\'' && in_double_brace == 0)
			in_brace ^= 1;
		else if (*ptr == '\"' && in_brace == 0)
			in_double_brace ^= 1;
		if (in_brace == 0 && in_double_brace == 0 && *ptr == c)
			break ;
		ptr++;
	}
	if (*ptr == '\0' && (in_brace != 0 || in_double_brace != 0))
		return (-1);
	return (ptr - *str);
}

static char	**remove_matrix(char **array)
{
	char	**ptr;

	if (array == NULL)
		return (NULL);
	ptr = array;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(array);
	return (NULL);
}

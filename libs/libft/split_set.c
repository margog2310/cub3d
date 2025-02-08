/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:55:46 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/08 23:44:02 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char c, const char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (printf("delimiter: %c\n", c), 1);
		delimiters++;
	}
	return (0);
}

static size_t	count_words(const char *s, const char *delimiters)
{
	size_t	count;

	count = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (is_delimiter(*s, delimiters))
			s++;
		if (*s)
			count++;
		while (!is_delimiter(*s, delimiters) && *s)
			s++;
	}
	return (count);
}

char	**split_set(const char *s, const char *delimiters)
{
	int			i;
	size_t		word_len;
	char		**arr;
	const char	*start;

	arr = malloc((count_words(s, delimiters) + 1) * sizeof(char *));
	if (!s || !arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (is_delimiter(*s, delimiters) && *s)
			s++;
		if (*s)
		{
			start = s;
			while (!is_delimiter(*s, delimiters) && *s)
				s++;
			word_len = s - start;
			arr[i++] = ft_substr(start, 0, word_len);
		}
	}
	arr[i] = NULL;
	return (arr);
}

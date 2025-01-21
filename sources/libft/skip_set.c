/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:15 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/21 19:09:14 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*skip_set(char *str, char *set)
{
	int			i;
	const char	*s;

	i = 0;
	while (*str)
	{
		s = set;
		while (*s)
		{
			if (*str == *s)
				break ;
			s++;
		}
		if (*s == '\0')
			break ;
		str++;
	}
	return (str);
}

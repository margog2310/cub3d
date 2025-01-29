/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:15 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/29 19:26:36 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*skip_set(char *str, char *set)
{
	const char	*s;

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

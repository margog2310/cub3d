/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:15 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/23 21:26:05 by ssottori         ###   ########.fr       */
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

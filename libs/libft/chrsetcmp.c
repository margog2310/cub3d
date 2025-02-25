/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrsetcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:13:42 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/25 17:14:02 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	chrsetcmp(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

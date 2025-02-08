/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_nbrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:30:24 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/08 22:31:30 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_nbrstr(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

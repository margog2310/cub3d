/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:32:20 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/22 21:46:56 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_unbrlen(unsigned int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putunbr_fd(int n, int fd)
{
	unsigned int	temp;

	temp = (unsigned int)n;
	if (temp > 9)
		ft_putunbr_fd(temp / 10, fd);
	ft_putchar_fd(temp % 10 + '0', fd);
	return ((int)ft_unbrlen(temp));
}

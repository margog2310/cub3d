/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:46:18 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/31 19:03:55 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rec_print(unsigned long n, const char *base)
{
	int	len;

	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	len = 0;
	if (n > (unsigned long)ft_strlen(base) - 1)
		len += rec_print(n / ft_strlen(base), base);
	len += ft_putchar_fd(*(base + (n % ft_strlen(base))), 1);
	return (len);
}

int	ft_print_ptr(void *ptr)
{
	unsigned long	n;
	const char		*base;
	int				len;

	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	n = (unsigned long)ptr;
	base = "0123456789abcdef";
	len = ft_putstr_fd("0x", 1);
	len += rec_print(n, base);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:19:54 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/22 22:46:38 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_flag(char flag, va_list args);

int	ft_printf(const char *fmt, ...)
{
	int		print_len;
	va_list	args;

	print_len = 0;
	va_start(args, fmt);
	while (*fmt != '\0')
	{
		if (*fmt != '%')
		{
			ft_putchar_fd(*fmt, 1);
			print_len++;
		}
		else
		{
			fmt++;
			print_len += ft_check_flag(*fmt, args);
		}
		fmt++;
	}
	va_end(args);
	return (print_len);
}

static int	ft_check_flag(char flag, va_list args)
{
	int	len;

	len = 0;
	if (flag == 'c')
		len += ft_putchar_fd(va_arg(args, int), 1);
	else if (flag == '%')
		len += ft_putchar_fd('%', 1);
	else if (flag == 's')
		len += ft_putstr_fd(va_arg(args, char *), 1);
	else if (flag == 'd' || flag == 'i')
		len += ft_putnbr_fd(va_arg(args, int), 1);
	else if (flag == 'u')
		len += ft_putunbr_fd(va_arg(args, int), 1);
	else if (flag == 'x')
		len += ft_puthexnbr(va_arg(args, unsigned int), 0);
	else if (flag == 'X')
		len += ft_puthexnbr(va_arg(args, unsigned int), 1);
	else if (flag == 'p')
		len += ft_print_ptr(va_arg(args, void *));
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:46:15 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/18 21:15:16 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t		len;
	char		*str;
	long int	num;

	num = n;
	len = ft_nbrlen(n);
	if (n < 0)
	{
		num *= -1;
		len++;
	}
	else if (n == 0)
		return ("0");
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len) = 0;
	while (len--)
	{
		*(str + len) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}

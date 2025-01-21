/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:35:55 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/22 19:48:49 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reverse_hex_array(char *hex_nbr, int len)
{
	int	j;

	j = 0;
	while (j < len / 2)
	{
		ft_swap_char(&hex_nbr[j], &hex_nbr[len - j - 1]);
		j++;
	}
}

int	ft_puthexnbr(unsigned int nbr, int uppercase)
{
	int		i;
	char	hex_nbr[32];
	char	*hex_base;

	if (uppercase)
		hex_base = "0123456789ABCDEF";
	else
		hex_base = "0123456789abcdef";
	i = 0;
	if (nbr == 0)
		hex_nbr[i++] = '0';
	else
	{
		while (nbr != 0)
		{
			hex_nbr[i++] = hex_base[nbr % 16];
			nbr /= 16;
		}
	}
	hex_nbr[i] = '\0';
	reverse_hex_array(hex_nbr, i);
	ft_putstr_fd(hex_nbr, 1);
	return (i);
}

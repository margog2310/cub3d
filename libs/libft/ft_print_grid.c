/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:50:02 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/07 20:17:07 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_grid(char **grid, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			write(1, &grid[i][j], 1);
			j++;
		}
		i++;
	}
}

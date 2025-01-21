/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:48:57 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 14:23:58 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_grid_size(char **grid, int *rows, int *cols)
{
	int	temp;

	*cols = 0;
	while (grid[*rows])
	{
		temp = 0;
		while (grid[*rows][temp])
			temp++;
		if (temp > *cols)
			*cols = temp;
		(*rows)++;
	}
}

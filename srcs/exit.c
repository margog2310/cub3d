/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:37:56 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/28 16:19:14 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_err(char *str)
{
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	exit(EXIT_FAILURE);
}

int	exit_win(t_mcraft *mcraft)
{
	if (mcraft->img)
		mlx_destroy_image(mcraft->mlx, mcraft->img);
	if (mcraft->win)
		mlx_destroy_window(mcraft->mlx, mcraft->win);
	free(mcraft->mlx);
	free(mcraft);
	ft_printf("Window closed. Exiting game...\n");
	exit(EXIT_SUCCESS);
}

void	cleanup_game(t_mcraft *mcraft)
{
	if (!mcraft)
		return;

	if (mcraft->map)
	{
		free_array(mcraft->map->grid);  // ✅ Free the map grid
		free(mcraft->map);
	}

	if (mcraft->img)
		mlx_destroy_image(mcraft->mlx, mcraft->img);
	if (mcraft->win)
		mlx_destroy_window(mcraft->mlx, mcraft->win);
	if (mcraft->mlx)
	{
		mlx_destroy_display(mcraft->mlx);
		free(mcraft->mlx);
	}
	free(mcraft);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:37:56 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/24 06:41:36 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_win(t_mcraft *mcraft)
{
	if (mcraft->img)
		mlx_destroy_image(mcraft->mlx, mcraft->img);
	if (mcraft->win)
		mlx_destroy_window(mcraft->mlx, mcraft->win);
	exit(0);
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
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}
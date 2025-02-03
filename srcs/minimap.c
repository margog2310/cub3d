/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:34:42 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/03 18:55:25 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_mcraft *mcraft, int start_x, int start_y, int color)
{
	int	y;
	int	x;

	y = start_y;
	while (y < start_y + TILE_S - 1)
	{
		x = start_x;
		while (x < start_x + TILE_S - 1)
		{
			draw_pixel(mcraft, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_map_loop(t_mcraft *mcraft)
{
	t_map	*map;
	int	i;
	int	j;
	int	color;

	map = mcraft->map;
	i = 0;
	while (i < map->rows - 1)
	{
		j = 0;
		while (j < map->cols - 1)
		{
			if (map->grid[i][j] == '1')
				color = WALL_COLOR;
			else if (map->grid[i][j] == '0')
				color = FLOOR_COLOR;
			else if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
					map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				color = PLAYER_COLOR;
			else
				color = FLOOR_COLOR;
			draw_tile(mcraft, OFF_X + (j * TILE_S), OFF_Y + (i * TILE_S), color);
			j++;
		}
		i++;
	}
}

void	minimap(t_mcraft *mcraft)
{
	// int	map_w;
	// int	map_h;

	// map_h = WIN_H / 5;
	// map_w = WIN_W / 5;
	draw_map_loop(mcraft);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:34:42 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/04 00:55:40 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_mcraft *mcraft, int start_x, int start_y, int tile_size, int color)
{
	int	y;
	int	x;

	y = start_y;
	while (y < start_y + tile_size - 1)
	{
		x = start_x;
		while (x < start_x + tile_size - 1)
		{
			draw_pixel(mcraft, x, y, color);
			x++;
		}
		y++;
	}
}

static void draw_player(t_mcraft *mcraft)
{
	int player_map_x, player_map_y;
	float scale = (float)TILE_S / BLOCK;  // World-to-minimap conversion factor

	player_map_x = OFF_X + (int)(mcraft->gamer.x * scale);
	player_map_y = OFF_Y + (int)(mcraft->gamer.y * scale);

	int marker_size = TILE_S / 2;
	draw_tile(mcraft, player_map_x - (marker_size / 2), 
			player_map_y - (marker_size / 2),
			marker_size,
			PLAYER_COLOR);
}

static void	draw_map_loop(t_mcraft *mcraft)
{
	t_map	*map;
	int		i;
	int		j;
	int		color;

	map = mcraft->map;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] == '1')
				color = WALL_COLOR;
			else if (map->grid[i][j] == '0')
				color = FLOOR_COLOR;
			else if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
					map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
					draw_player(mcraft);
			else
				break;
			draw_tile(mcraft, OFF_X + (j * TILE_S), OFF_Y + (i * TILE_S), TILE_S, color);
			j++;
		}
		i++;
	}
}

void	minimap(t_mcraft *mcraft)
{
	draw_map_loop(mcraft);
	draw_player(mcraft);
	move_player(mcraft);
}

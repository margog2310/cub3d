/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:34:42 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/04 04:11:14 by ssottori         ###   ########.fr       */
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
	int		player_map_x;
	int		player_map_y;
	float	scale;
	int		marker_size;

	scale = (float)TILE_S / BLOCK;
	player_map_x = OFF_X + (int)(mcraft->gamer.x * scale);
	player_map_y = OFF_Y + (int)(mcraft->gamer.y * scale);
	marker_size = TILE_S / 2;
	draw_tile(mcraft, player_map_x, 
			player_map_y,
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
					color = PLAYER_COLOR;
			else
				break;
			draw_tile(mcraft, OFF_X + (j * TILE_S), OFF_Y + (i * TILE_S), TILE_S, color);
			j++;
		}
		i++;
	}
}

void draw_ray_minimap(t_mcraft *mcraft)
{
	float	scale = (float)TILE_S / BLOCK; //make it minimap instead of real world
	float	ray_x, ray_y;
	float	angle;
	int		map_index_x;
	int		map_index_y;
	int		mini_x;
	int		mini_y;
	
	ray_x = mcraft->gamer.x; //players start pos
	ray_y = mcraft->gamer.y;
	angle = mcraft->gamer.angle;
	while (1)
	{
		map_index_x = (int)(ray_x / BLOCK);
		map_index_y = (int)(ray_y / BLOCK);
		if (map_index_x < 0 || map_index_x >= mcraft->map->cols ||
			map_index_y < 0 || map_index_y >= mcraft->map->rows) //check if OOB
			break ;
		if (mcraft->map->grid[map_index_y][map_index_x] == '1')
			break ;
		mini_x = OFF_X + (int)(ray_x * scale); //convert to minimp coords
		mini_y = OFF_Y + (int)(ray_y * scale);
		draw_pixel(mcraft, mini_x, mini_y, RAY_COLOR);
		ray_x += cos(angle) * STEP_SIZE;
		ray_y -= sin(angle) * STEP_SIZE;
	}
}

void	minimap(t_mcraft *mcraft)
{
	draw_map_loop(mcraft);
	draw_player(mcraft);
	move_player(mcraft);
	draw_ray_minimap(mcraft);
}

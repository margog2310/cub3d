/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:34:42 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/08 22:35:01 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(t_mcraft *mcraft)
{
	int		player_map_x;
	int		player_map_y;
	float	scale;
	int		marker_size;

	// int		minimap_h;
	// minimap_h = WIN_H / 5; //was trying to fix fuckin movement inversion
	scale = (float)TILE_S / BLOCK;
	player_map_x = OFF_X + (int)(mcraft->gamer->x * scale);
	player_map_y = OFF_Y + (int)(mcraft->gamer->y * scale);
	marker_size = TILE_S / 2;
	draw_tile(mcraft, player_map_x - (marker_size / 2), player_map_y
		- (marker_size / 2), marker_size, PLAYER_COLOR);
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
			else if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				color = PLAYER_COLOR;
			else
				break ;
			draw_tile(mcraft, OFF_X + (j * TILE_S), OFF_Y + (i * TILE_S),
				TILE_S, color);
			j++;
		}
		i++;
	}
}

void	draw_ray_minimap(t_mcraft *mcraft, float angle)
{
	float		scale;
	float		ray_x;
	float		ray_y;
	t_vector	hit;
	int			mini_x;
	int			mini_y;

	hit = mr_ray(mcraft, angle);
	ray_x = mcraft->gamer->x;
	ray_y = mcraft->gamer->y;
	scale = (float)TILE_S / BLOCK; // minimap size it
	while ((int)(ray_x / BLOCK) != (int)(hit.x / BLOCK) || (int)(ray_y
			/ BLOCK) != (int)(hit.y / BLOCK))
	{
		mini_x = OFF_X + (int)(ray_x * scale);
		mini_y = OFF_Y + (int)(ray_y * scale);
		draw_pixel(mcraft, mini_x, mini_y, RAY_COLOR);
		ray_x += cos(angle) * STEP_SIZE;
		ray_y += sin(angle) * STEP_SIZE;
	}
}

void	minimap(t_mcraft *mcraft)
{
	draw_map_loop(mcraft);
	draw_player(mcraft);
	move_player(mcraft);
	cast_rays(mcraft);
}
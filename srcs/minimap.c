/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:34:42 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 17:16:02 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(t_mcraft *mcraft)
{
	t_pos	player_map;
	int		marker_size;

	player_map.x = OFF_X + (int)(mcraft->gamer->grid_x);
	player_map.y = OFF_Y + (int)(mcraft->gamer->grid_y);
	marker_size = TILE_S / 2;
	draw_tile(mcraft, (t_pos){player_map.x - (marker_size),
		player_map.y - (marker_size)},
		marker_size, PLAYER_COLOR);
}

static void	draw_map_loop(t_mcraft *mcraft)
{
	t_map	*map;
	int		i;
	int		j;
	int		color;

	map = mcraft->map;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (map->grid[i][j] == '1')
				color = WALL_COLOR;
			else if (map->grid[i][j] == '0' || chrsetcmp(map->grid[i][j], WHITESPACE))
				color = FLOOR_COLOR;
			else if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				color = PURPLE_GRAY;
			else
				break ;
			draw_tile(mcraft, (t_pos){OFF_X + (j * TILE_S),
				OFF_Y + (i * TILE_S)}, TILE_S, color);
		}
	}
}

void	draw_ray_minimap(t_mcraft *mcraft, float angle, float scale)
{
	float		ray_x;
	float		ray_y;
	t_vector	hit;
	int			mini_x;
	int			mini_y;

	hit = mr_ray(mcraft, angle);
	ray_x = mcraft->gamer->grid_x;
	ray_y = mcraft->gamer->grid_y;
	while ((int)(ray_x / BLOCK) != (int)(hit.x / BLOCK) || (int)(ray_y
			/ BLOCK) != (int)(hit.y / BLOCK))
	{
		mini_x = OFF_X + (int)(ray_x * scale);
		mini_y = OFF_Y + (int)(ray_y * scale);
		if (mini_x < 0 || mini_y < 0 || mini_x > WIN_W || mini_y > WIN_H)
			break ;
		if (mcraft->map->grid[(int)(ray_y / TILE_S)]
			[(int)(ray_x / TILE_S)] == '1')
			break ;
		draw_pixel(mcraft, mini_x, mini_y, RAY_COLOR);
		ray_x += cos(angle) * STEP_SIZE;
		ray_y += sin(angle) * STEP_SIZE;
	}
}

void	draw_crosshairs(t_mcraft *mcraft, int color)
{
	int	mid_x;
	int	mid_y;
	int	len;
	int	x;
	int	y;

	mid_x = WIN_W / 2;
	mid_y = WIN_H / 2;
	len = 10;
	x = mid_x - len;
	while (x <= mid_x + len)
	{
		draw_pixel(mcraft, x, mid_y, color);
		x++;
	}
	y = mid_y - len;
	while (y <= mid_y + len)
	{
		draw_pixel(mcraft, mid_x, y, color);
		y++;
	}
}

void	minimap(t_mcraft *mcraft)
{
	draw_map_loop(mcraft);
	draw_player(mcraft);
	move_player(mcraft);
	cast_rays(mcraft);
}

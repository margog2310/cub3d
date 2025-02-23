/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:50:12 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/23 04:02:35 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x * y * y));
}

t_vector	mr_ray(t_mcraft *mcraft, float angle)
{
	float		ray_x;
	float		ray_y;
	int			map_x;
	int			map_y;
	t_vector	bullseye;

	ray_x = mcraft->gamer->x;
	ray_y = mcraft->gamer->y;
	while (1)
	{
		map_x = (int)(ray_x / BLOCK);
		map_y = (int)(ray_y / BLOCK);
		if (map_x < 0 || map_x >= mcraft->map->cols || map_y < 0
			|| map_y >= mcraft->map->rows)
			break ;
		if (mcraft->map->grid[map_y][map_x] == '1')
			break ;
		ray_x += cos(angle) * STEP_SIZE;
		ray_y += sin(angle) * STEP_SIZE;
	}
	bullseye.x = ray_x;
	bullseye.y = ray_y;
	return (bullseye);
}

/*
void	mr_3d_raycast(t_mcraft *mcraft, float angle, int screen_x)
{
	t_vector	hit;
	float		dist;
	float		wall_height;
	int			start_y;
	int			end_y;
	int			y;

	hit = mr_ray(mcraft, angle);
	dist = sqrt((hit.x - mcraft->gamer->x) * (hit.x - mcraft->gamer->x) +
				(hit.y - mcraft->gamer->y) * (hit.y - mcraft->gamer->y));
	
	dist *= cos(angle - mcraft->gamer->angle); // Fisheye correction

	wall_height = (BLOCK / dist) * (WIN_W / 2);
	start_y = (WIN_H - wall_height) / 2;
	end_y = start_y + wall_height;
	y = start_y;
	while (y < end_y)
	{
		draw_pixel(mcraft, screen_x, y, N_WALL);
		y++;
	}
}

void	many_rays(t_mcraft *mcraft)
{
	float	start_a;
	float	end_a;
	float	i;
	float	angle;
	int		screen_x;

	start_a = mcraft->gamer->angle - (PI / 6);
	end_a = mcraft->gamer->angle + (PI / 6);
	i = (PI / 3) / WIN_W; // Angle increment to spread rays across the FOV

	angle = start_a;
	screen_x = 0;
	while (angle <= end_a)
	{
		mr_3d_raycast(mcraft, angle, screen_x);
		angle += i;
		screen_x++;
	}
}*/

/* 3D raycasting
- find hitpoint with mr ray
- calculate distance from block and determine  or calculate wall height
- draw map in 3D
- make a helper function to check what direction the
	ray is hitting. so we can set the different textures
- make sure player start point is correct
- fisheye?? check how to deal with fisheye*/

void	cast_rays(t_mcraft *mcraft)
{
	float	start_a;
	float	end_a;
	float	i;
	float	angle;
	float	scale;

	scale = (float)TILE_S / BLOCK;
	start_a = mcraft->gamer->angle - (PI / 6);
	end_a = mcraft->gamer->angle + (PI / 6);
	i = (PI / 3) / WIN_W;
	angle = start_a;
	while (angle <= end_a)
	{
		draw_ray_minimap(mcraft, angle, scale);
		angle += i;
	}
}

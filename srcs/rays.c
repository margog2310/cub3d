/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:50:12 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/21 23:33:55 by mganchev         ###   ########.fr       */
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

	start_a = mcraft->gamer->angle - (PI / 6);
	end_a = mcraft->gamer->angle + (PI / 6);
	i = (PI / 3) / WIN_W;
	angle = start_a;
	while (angle <= end_a)
	{
		draw_ray_minimap(mcraft, angle);
		angle += i;
	}
}

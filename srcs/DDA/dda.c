/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:03:48 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/22 19:38:45 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_step_and_sidedist(t_gamer *gamer, t_ray *ray, t_pos *map_pos,
		t_pos *step)
{
	if (ray->ray_dir_x < 0)
	{
		step->x = -1;
		ray->side_dist_x = (gamer->x - map_pos->x) * ray->delta_dist_x;
	}
	else
	{
		step->x = 1;
		ray->side_dist_x = (map_pos->x + 1.0 - gamer->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		step->y = -1;
		ray->side_dist_y = (gamer->y - map_pos->y) * ray->delta_dist_y;
	}
	else
	{
		step->y = 1;
		ray->side_dist_y = (map_pos->y + 1.0 - gamer->y) * ray->delta_dist_y;
	}
}

int	find_wall(t_mcraft *mcraft, t_ray *ray, t_pos *map_pos)
{
	int	hit;

	hit = 0;
	calculate_step_and_sidedist(mcraft->gamer, ray, map_pos, &ray->step);
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			map_pos->x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			map_pos->y += ray->step.y;
			ray->side = 1;
		}
		if (!is_cell_valid(mcraft->map, map_pos->y, map_pos->x))
			return (0);
		if (mcraft->map->grid[map_pos->y][map_pos->x] == WALL)
			return (1);
	}
	return (0);
}

int	dda(t_mcraft *mcraft)
{
	int		x;
	t_pos	map_pos;
	t_ray	*ray;

	x = 0;
	while (x < mcraft->w)
	{
		map_pos.x = (int)mcraft->gamer->x;
		map_pos.y = (int)mcraft->gamer->y;
		ray = init_ray(mcraft, x);
		find_wall(mcraft, ray, &map_pos);
		setup_ray(mcraft, ray, map_pos);
		draw_vector(mcraft, ray, map_pos, x);
		x++;
		free(ray);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:03:48 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/13 23:30:30 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*init_ray(t_mcraft *mcraft, t_pos dir, int x)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit_err("Memory allocation failed.");
	ray->direction = mcraft->gamer->direction;
	mcraft->camera_x = 2 * x / (double)mcraft->w - 1;
	mcraft->plane_x = -dir.y * 0.66;
	mcraft->plane_y = dir.x * 0.66;
	ray->ray_dir_x = dir.x + mcraft->plane_x * mcraft->camera_x;
	ray->ray_dir_y = dir.y + mcraft->plane_y * mcraft->camera_x;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->h = mcraft->camera_h;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->curr_x = 0;
	ray->curr_y = 0;
	return (ray);
}

void	calculate_step_and_sideDist(t_gamer *gamer, t_ray *ray, t_pos *map_pos,
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

int	find_wall(t_mcraft *mcraft, t_ray *ray, t_pos *map_pos, int *side)
{
	t_pos	step;

	calculate_step_and_sideDist(mcraft->gamer, ray, map_pos, &step);
	while (1)
	{
		
        if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			map_pos->x += step.x;
			*side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			map_pos->y += step.y;
			*side = 1;
		}
        if (!is_cell_valid(mcraft->map, map_pos->y, map_pos->x))
            break ;
		if (mcraft->map->grid[map_pos->y][map_pos->x] == WALL)
			return (1);
	}
	return (0);
}

int	dda(t_mcraft *mcraft)
{
	int x;
	int hit;
	int side;
	t_pos map_pos;
	t_pos dir;
	t_ray *ray;

	x = 0;
	dir = set_direction_vector(mcraft->gamer);
	map_pos.x = (int)mcraft->gamer->x;
	map_pos.y = (int)mcraft->gamer->y;
	while (x < mcraft->w)
	{
		ray = init_ray(mcraft, dir, x);
		hit = find_wall(mcraft, ray, &map_pos, &side);
		if (hit)
		{
			ray->draw_start = map_pos.x * BLOCK;
			ray->draw_end = ray->draw_start + BLOCK;
			ray->curr_x = map_pos.x;
			ray->curr_y = map_pos.y;
			draw_tile(mcraft, ray->draw_start, ray->draw_end, 64,
				mcraft->txts->floor_color);
		}
		x++;
	}
	return (0);
}
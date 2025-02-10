/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:00:37 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/10 20:09:48 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	**init_visited(t_map *map)
{
	bool	**visited;

	visited = (bool **)ft_allocate_grid(map->rows, map->cols, sizeof(bool));
	if (!visited)
	{
		free(visited);
		exit_err("Memory allocation failed.");
	}
	return (visited);
}

void	init_ray(t_ray *ray, t_mcraft *mcraft, t_pos dir, int x)
{
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
}

void	calculate_step_and_sideDist(t_gamer *gamer, t_ray *ray, t_pos *map_pos,
		t_pos *step)
{
	if (ray->ray_dir_x < 0)
	{
		step->x = -1;
		ray->side_dist_x = (gamer->x / BLOCK - map_pos->x) * ray->delta_dist_x;
	}
	else
	{
		step->x = 1;
		ray->side_dist_x = (map_pos->x + 1.0 - gamer->x / BLOCK)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_x < 0)
	{
		step->y = -1;
		ray->side_dist_y = (gamer->y / BLOCK - map_pos->y) * ray->delta_dist_y;
	}
	else
	{
		step->y = 1;
		ray->side_dist_y = (map_pos->y + 1.0 - gamer->y / BLOCK)
			* ray->delta_dist_y;
	}
}

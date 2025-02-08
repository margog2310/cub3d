/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:00:37 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/08 21:57:56 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos	set_direction_vector(t_gamer *gamer)
{
	t_pos	direction;

	direction.x = 0;
	direction.y = 0;
	if (gamer->direction == NORTH)
	{
		direction.x = 0;
		direction.y = -1;
	}
	else if (gamer->direction == SOUTH)
	{
		direction.x = 0;
		direction.y = 1;
	}
	else if (gamer->direction == WEST)
	{
		direction.x = 1;
		direction.y = 0;
	}
	else if (gamer->direction == EAST)
	{
		direction.x = -1;
		direction.y = 0;
	}
	return (direction);
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

t_pos	dda(t_mcraft *mcraft, bool **visited, t_pos dir)
{
	int		x;
	int		hit;
	int		side;
	t_pos	end;
	t_pos	step;
	t_pos	map_pos;
	t_ray	ray;

	x = 0;
	end.x = 0;
	end.y = 0;
	map_pos.x = (int)mcraft->gamer->x / BLOCK;
	map_pos.y = (int)mcraft->gamer->y / BLOCK;
    printf("player x: %f y: %f\n", mcraft->gamer->x / BLOCK, mcraft->gamer->y / BLOCK);
	while (1)
	{
		while (x < mcraft->w)
		{
			init_ray(&ray, mcraft, dir, x);
			calculate_step_and_sideDist(mcraft->gamer, &ray, &map_pos, &step);
			hit = 0;
			while (hit == 0)
			{
				if (ray.side_dist_x < ray.side_dist_y)
				{
					ray.side_dist_x += ray.delta_dist_x;
					map_pos.x += step.x;
					side = 0;
				}
				else
				{
					ray.side_dist_y += ray.delta_dist_y;
					map_pos.y += step.y;
					side = 1;
				}
				if (map_pos.y >= 0 && map_pos.y < mcraft->map->rows &&
                    map_pos.x >= 0 && map_pos.x < mcraft->map->cols)
                {
                    visited[map_pos.y][map_pos.x] = true;
                    if (mcraft->map->grid[map_pos.y][map_pos.x] == WALL)
                    {
                        hit = 1;
                        end.x = map_pos.x;
                        end.y = map_pos.y;
                        return (end);
                    }
                }
                else
                {
                    // Out of bounds
                    hit = 1;
                    dir.x = -1;
                    dir.y = -1;
                    return dir;
                }
			}
			if (side == 0)
				ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
			else
				ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
			x++;
		}
	}
    end.x = 0;
    end.y = 0;
	return (end);
}

void	dfs(t_mcraft *mcraft)
{
	t_pos start;
	t_pos end;
	t_pos dir;
	bool **visited;

	visited = (bool **)ft_allocate_grid(mcraft->map->rows, mcraft->map->cols, sizeof(bool));
    if (!visited)
    {
        free(visited);
        exit_err("Memory allocation failed.");
    }
	start.x = (int)mcraft->gamer->x / BLOCK;
	start.y = (int)mcraft->gamer->y / BLOCK;
	dir = set_direction_vector(mcraft->gamer);
	end = dda(mcraft, visited, dir);
	printf("end x: %d end y: %d\n", end.x, end.y);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:06:28 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/13 21:14:29 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_wall(t_mcraft *mcraft, t_ray *ray, t_pos *map_pos, bool **visited,
		int *side)
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
		visited[map_pos->y][map_pos->x] = true;
		if (mcraft->map->grid[map_pos->y][map_pos->x] == WALL)
			return (1);
	}
	return (0);
}

t_pos	dda(t_mcraft *mcraft, bool **visited, t_pos dir, t_pos end)
{
	int		x;
	int		hit;
	int		side;
	t_pos	map_pos;
	t_ray	ray;

	x = 0;
	map_pos.x = (int)mcraft->gamer->x / BLOCK;
	map_pos.y = (int)mcraft->gamer->y / BLOCK;
	while (1)
	{
		while (x < mcraft->w)
		{
			init_ray(&ray, mcraft, dir, x);
			hit = find_wall(mcraft, &ray, &map_pos, visited, &side);
			if (hit)
			{
				ray.draw_start = map_pos.y * BLOCK;
                ray.draw_end = ray.draw_start + BLOCK;
                end.x = map_pos.x;
				end.y = map_pos.y;
				ray.curr_x = end.x;
				ray.curr_y = end.y;
				draw_ray(mcraft, &ray);
				return (end);
			}
			if (side == 0)
				ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
			else
				ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		}
		x++;
	}
	return (end);
}

void	dfs(t_mcraft *mcraft)
{
	t_pos	start;
	t_pos	end;
	t_pos	dir;
	bool	**visited;

	visited = init_visited(mcraft->map);
	start.x = (int)mcraft->gamer->x / BLOCK;
	start.y = (int)mcraft->gamer->y / BLOCK;
	end.x = 0;
	end.y = 0;
	dir = set_direction_vector(mcraft->gamer);
	end = dda(mcraft, visited, dir, end);
	printf("end x: %d end y: %d\n", end.x, end.y);
	// end is currently the coordinates of the nearest wall
}

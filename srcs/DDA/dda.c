/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:03:48 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/15 19:19:21 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*init_ray(t_mcraft *mcraft, t_pos dir, int x)
{
	t_ray	*ray;
	double	plane_dist;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit_err("Memory allocation failed.");
	ray->direction = mcraft->gamer->direction;
	mcraft->camera_x = 2 * x / (double)mcraft->w - 1;
	plane_dist = tan((FOV / 2.0) * (PI / 180.0));
	mcraft->plane_x = -dir.y * plane_dist;
	mcraft->plane_y = dir.x * plane_dist;
	ray->ray_dir_x = dir.x + mcraft->plane_x * mcraft->camera_x;
	ray->ray_dir_y = dir.y + mcraft->plane_y * mcraft->camera_x;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->curr_x = 0;
	ray->curr_y = 0;
	// printf("Ray initialized: dir_x=%f, dir_y=%f\n", ray->ray_dir_x,
	//	ray->ray_dir_y);
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
	calculate_step_and_sideDist(mcraft->gamer, ray, map_pos, &ray->step);
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			map_pos->x += ray->step.x;
			*side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			map_pos->y += ray->step.y;
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
	int color;
	t_pos map_pos;
	t_pos dir;
	t_ray *ray;
	t_vector vector;

	x = 0;
	dir = set_direction_vector(mcraft->gamer);
	while (x < mcraft->w)
	{
		map_pos.x = (int)mcraft->gamer->x;
		map_pos.y = (int)mcraft->gamer->y;
		ray = init_ray(mcraft, dir, x);
		hit = find_wall(mcraft, ray, &map_pos, &side);
		if (hit)
		{
			if (side == 0)
				ray->perp_wall_dist = (map_pos.x - mcraft->gamer->x + (1
							- ray->step.x) / 2) / ray->ray_dir_x;
			else
				ray->perp_wall_dist = (map_pos.y - mcraft->gamer->y + (1
							- ray->step.y) / 2) / ray->ray_dir_y;
			// printf("hit\n");
			vector.h = (int)(mcraft->h / ray->perp_wall_dist);
			vector.y0 = -vector.h / 2 + mcraft->h / 2;
			if (vector.y0 < 0)
				vector.y0 = 0;
			vector.y1 = vector.h / 2 + mcraft->h / 2;
			if (vector.y1 >= mcraft->h)
				vector.y1 = mcraft->h - 1;
			ray->curr_x = map_pos.x;
			ray->curr_y = map_pos.y;
			if (side == 0)
				vector.tex_x = (int)((mcraft->gamer->y + ray->perp_wall_dist
							* ray->ray_dir_y) * mcraft->txts->tx_width)
					% mcraft->txts->tx_width;
			else
				vector.tex_x = (int)((mcraft->gamer->x + ray->perp_wall_dist
							* ray->ray_dir_x) * mcraft->txts->tx_width)
					% mcraft->txts->tx_width;
			// printf("vector y0: %d y1: %d\n", vector.y0, vector.y1);
			// sleep(20000);
			for (vector.y = 0; vector.y < vector.y0; vector.y++)
			{
				draw_pixel(mcraft, x, vector.y, SKY); // Use blue color
			}
			for (vector.y = vector.y0; vector.y < vector.y1; vector.y++)
			{
				vector.tex_y = ((vector.y * 2 - mcraft->h + vector.h)
						* mcraft->txts->tx_width) / vector.h / 2;
				color = get_texture_color(mcraft, mcraft->txts, vector.tex_x,
						vector.tex_y);
				// draw_pixel(mcraft, x, vector.y, color);
				texture_on_img(mcraft, ray, vector);
			}
			for (vector.y = vector.y1; vector.y < mcraft->h; vector.y++)
				draw_pixel(mcraft, x, vector.y, FLOOR);
		}
		x++;
		free(ray);
	}
	return (0);
}

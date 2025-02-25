/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:07:58 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/24 06:38:59 by margo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*init_ray(t_mcraft *mcraft, int x)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit_err("Memory allocation failed.");
	ray->direction = mcraft->gamer->direction;
	mcraft->camera_x = 2 * x / (double)mcraft->w - 1;
	ray->ray_dir_x = mcraft->gamer->dir_x + mcraft->plane_x * mcraft->camera_x;
	ray->ray_dir_y = mcraft->gamer->dir_y + mcraft->plane_y * mcraft->camera_x;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->side = -1;
	return (ray);
}

void	setup_ray(t_mcraft *mcraft, t_ray *ray, t_pos map_pos)
{
	ray->wall_x = 0.0;
	ray->curr_x = map_pos.x;
	ray->curr_y = map_pos.y;
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (map_pos.x - mcraft->gamer->x + (1 - ray->step.x) / 2) / ray->ray_dir_x;
		ray->wall_x = mcraft->gamer->y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->perp_wall_dist = (map_pos.y - mcraft->gamer->y + (1 - ray->step.y) / 2) / ray->ray_dir_y;
		ray->wall_x = mcraft->gamer->x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	if (ray->perp_wall_dist < 1e-6)
		ray->perp_wall_dist = 1e-6;
	ray->wall_x -= floor(ray->wall_x);
}

void	setup_vector(t_mcraft *mcraft, t_ray *ray, t_vector *vector, int x)
{
	t_img	*tx_data;

	tx_data = get_tx_data(get_tx_index(ray), mcraft->txts);
	vector->h = mcraft->h / ray->perp_wall_dist;
	vector->x = x;
	vector->tex_x = (int)(ray->wall_x * (double)(tx_data->w));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		vector->tex_x = tx_data->w - vector->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		vector->tex_x = tx_data->w - vector->tex_x - 1;
	vector->y0 = -vector->h / 2 + mcraft->h / 2;
	if (vector->y0 < 0)
		vector->y0 = 0;
	vector->y1 = vector->h / 2 + mcraft->h / 2;
	if (vector->y1 >= mcraft->h)
		vector->y1 = mcraft->h - 1;
}

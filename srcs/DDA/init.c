/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:07:58 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/15 23:49:19 by mganchev         ###   ########.fr       */
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
	printf("Ray direction: x=%f, y=%f\n", ray->ray_dir_x, ray->ray_dir_y);
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
	return (ray);
}

void	setup_ray(t_mcraft *mcraft, t_ray *ray, t_pos map_pos)
{
	ray->wall_x = 0.0;
	ray->curr_x = map_pos.x;
	ray->curr_y = map_pos.y;
	if (ray->side == 0) // hit on x axis
	{
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		ray->wall_x = mcraft->gamer->y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else // hit on y axis;
	{
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
		ray->wall_x = mcraft->gamer->x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
}

void    setup_vector(t_mcraft *mcraft, t_ray *ray, t_vector *vector)
{
	vector->h = (int)(mcraft->h / ray->perp_wall_dist);
	vector->x = ray->curr_x;
    vector->tex_x = (int)(ray->wall_x * (double)(mcraft->txts->tx_width));
    if (ray->side == 0 && ray->ray_dir_x > 0)
        vector->tex_x = mcraft->txts->tx_width - vector->tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        vector->tex_x = mcraft->txts->tx_width - vector->tex_x - 1;
    vector->y0 = -vector->h / 2 + mcraft->h / 2;
    if (vector->y0 < 0)
        vector->y0 = 0;
    vector->y1 = vector->h / 2 + mcraft->h / 2;
    if (vector->y1 >= mcraft->h)
        vector->y1 = mcraft->h - 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:18:57 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/13 23:11:37 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector    *init_vector(t_ray *ray)
{
    t_vector *vector;

    vector = malloc(sizeof(t_vector));
    if (!vector)
        return (NULL);
    vector->x = ray->curr_x * BLOCK;
    vector->y = 0;
    vector->y0 = 0;
    vector->y1 = ray->draw_start;
    vector->tex_x = 0;
    vector->tex_y = 0;
    return (vector);
}

void    paint_line(t_mcraft *mcraft, t_vector *vector, int rgb)
{
    int y;
    int y_max;

    if (vector->y0 < vector->y1)
    {
        y = vector->y0;
        y_max = vector->y1;
    }
    else
    {
        y = vector->y1;
        y_max = vector->y0;
    }
    if (y >= 0)
    {
        while (y < y_max)
        {
            draw_pixel(mcraft, vector->x, y, rgb);
            y++;
        }
    }
}

void    draw_ray(t_mcraft *mcraft, t_ray *ray)
{
    t_vector *vector;
    double  wall_x;

    wall_x = 0.0;
    vector = init_vector(ray);
    if (ray->direction == WEST || ray->direction == EAST)
		wall_x = mcraft->gamer->y * BLOCK + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = mcraft->gamer->x * BLOCK + ray->perp_wall_dist * ray->ray_dir_x;
    vector->tex_x = (int)(wall_x * 64.0);
    paint_line(mcraft, vector, mcraft->txts->ceiling_color);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:55:22 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/08 23:32:11 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
    TO DO:
        1. allocate the rest of ray struct data properly
        2. draw singular line
        3. draw texture line
        4. draw entire texture
        5. pass img ptr for appropriate texture
*/

// void	paint_texture_line(t_mcraft *mcraft, t_vector vector, void *tx_img)
// {
// 	int y;
// 	int y_max;

//     if (vector.y0 < vector.y1)
//     {
//         y = vector.y0;
//         y_max = vector.y1;
//     }
//     else
//     {
//         y = vector.y1;
//         y_max = vector.y0;
//     }
//     if (y >= 0)
//     {
//         while (y < y_max)
//         {
//             draw_pixel(mcraft, vector.x, y, tx_img);
//             y++;
//         }
//     }
// }

void    paint_line(t_mcraft *mcraft, t_vector vector, int rgb)
{
    int y;
	int y_max;

    if (vector.y0 < vector.y1)
    {
        y = vector.y0;
        y_max = vector.y1;
    }
    else
    {
        y = vector.y1;
        y_max = vector.y0;
    }
    if (y >= 0)
    {
        while (y < y_max)
        {
            draw_pixel(mcraft, vector.x, y, rgb);
            y++;
        }
    }
}


void    draw_ray(t_mcraft *mcraft, t_ray *ray)
{
    t_vector    vector;
    double wall_x;
    
    if (ray->direction == WEST || ray->direction == EAST)
        wall_x = mcraft->gamer->y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = mcraft->gamer->x + ray->perp_wall_dist *ray->ray_dir_x;
    vector.x = ray->curr_x;
    vector.y0 = 0; // reset vector to start at top pixel
    vector.y1 = ray->draw_start; // reset vector end to end at the beginning pixel
    paint_line(mcraft, vector, mcraft->txts->ceiling_color);
    vector.y0 = ray->draw_start;
    vector.y1 = ray->draw_end;
    //paint_texture_line(mcraft, vector, mcraft->txts->tx_n_img);
    vector.y0 = ray->draw_end; // reset vector to start at end pixel of texture
    vector.y1 = WIN_H; // reset vector to end at the bottom pixel
    paint_line(mcraft, vector, mcraft->txts->floor_color);
}

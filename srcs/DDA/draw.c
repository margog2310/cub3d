/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:18:57 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/15 23:14:47 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_on_img(t_mcraft *mcraft, t_vector vector, char *tx_data)
{
	int		scale;
	int		tx_pos;
	int		img_pos;
	int		tx_size;
	int		img_size;
    
	scale = vector.y * mcraft->ll - (mcraft->h * mcraft->camera_h) * mcraft->ll
		/ 2 + vector.h * mcraft->ll / 2;
	vector.tex_y = ((scale * mcraft->txts->tx_height) / vector.h) / mcraft->ll;
	img_pos = vector.y * mcraft->ll + vector.x * (mcraft->bpp / 8);
	tx_pos = vector.tex_y * mcraft->ll + vector.tex_x * (mcraft->bpp / 8);
	img_size = mcraft->w * mcraft->h * (mcraft->bpp / 8);
	tx_size = mcraft->txts->tx_width * mcraft->txts->tx_height * (mcraft->bpp
			/ 8);
	if (img_pos >= 0 && img_pos < img_size && tx_pos >= 0 && tx_pos < tx_size)
		mcraft->img_addr[img_pos] = tx_data[tx_pos];
}

void	paint_line(t_mcraft *mcraft, t_vector vector, int rgb)
{
	int	y;
	int	y_max;

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
			vector.y = y;
            pixel_on_img(mcraft, rgb, vector.x, y);
            //draw_pixel(mcraft, vector.x, y, rgb);
			y++;
		}
	}
}

void    paint_texture_line(t_mcraft *mcraft, t_ray *ray, t_vector vector)
{
    int y;
    int y_max;
    char    *tx_data;

    tx_data = get_tx_data(get_tx_index(ray->direction), mcraft->txts);
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
            vector.y = y;
            texture_on_img(mcraft, vector, tx_data);
            y++;        
        }
    }
}

void    pixel_on_img(t_mcraft *mcraft, int rgb, int x, int y)
{
    int r;
    int g;
    int b;

    r = (rgb >> 16) & 0xFF;
    g = (rgb >> 8) & 0xFF;
    b = rgb & 0xFF;
    mcraft->img_addr[y * mcraft->ll + x * mcraft->bpp / 8] = b;
    mcraft->img_addr[y * mcraft->ll + (x * mcraft->bpp / 8) + 1] = g;
    mcraft->img_addr[y * mcraft->ll + (x * mcraft->bpp / 8) + 2] = r;
}

void	draw_vector(t_mcraft *mcraft, t_ray *ray, t_pos map_pos)
{
	t_vector vector;

    setup_vector(mcraft, ray, &vector);
    if (mcraft->map->grid[map_pos.y][map_pos.x] == '1')
		paint_texture_line(mcraft, ray, vector);
    vector.y0 = 0;
    vector.y1 = -vector.h / 2 + mcraft->h / 2;
    if (vector.y0 < 0)
        vector.y0 = 0;
    paint_line(mcraft, vector, mcraft->txts->ceiling_color);
    vector.y0 = mcraft->h;
    vector.y1 = vector.h / 2 + mcraft->h / 2;
    if (vector.y1 >= mcraft->h)
        vector.y1 = mcraft->h - 1;
    paint_line(mcraft, vector, mcraft->txts->floor_color);
    // if (ray->side == 0)
    //     vector.tex_x = (int)((mcraft->gamer->y + ray->perp_wall_dist
    //                 * ray->ray_dir_y) * mcraft->txts->tx_width)
    //         % mcraft->txts->tx_width;
    // else
    //     vector.tex_x = (int)((mcraft->gamer->x + ray->perp_wall_dist
    //                 * ray->ray_dir_x) * mcraft->txts->tx_width)
    //         % mcraft->txts->tx_width;
    // // printf("vector y0: %d y1: %d\n", vector.y0, vector.y1);
    // // sleep(20000);
    // for (vector.y = 0; vector.y < vector.y0; vector.y++)
    // {
    //     draw_pixel(mcraft, x, vector.y, SKY); // Use blue color
    // }
    // for (vector.y = vector.y0; vector.y < vector.y1; vector.y++)
    // {
    //     vector.tex_y = ((vector.y * 2 - mcraft->h + vector.h)
    //             * mcraft->txts->tx_width) / vector.h / 2;
    //     color = get_texture_color(mcraft, mcraft->txts, vector.tex_x,
    //             vector.tex_y);
    //     // draw_pixel(mcraft, x, vector.y, color);
    //     texture_on_img(mcraft, ray, vector);
    // }
    // for (vector.y = vector.y1; vector.y < mcraft->h; vector.y++)
    //     draw_pixel(mcraft, x, vector.y, FLOOR);
}

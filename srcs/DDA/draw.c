/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:55:22 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/10 20:15:51 by mganchev         ###   ########.fr       */
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

// need to fix this entire function, nothing is being calculated properly
void	texture_on_img(t_mcraft *mcraft, t_ray *ray, t_vector vector)
{
	int	scale;
	int	tx_pos;
	int	img_pos;
	int	tx_index;

    printf("debug: ll: %d\n", mcraft->ll);
    printf("debug: tx h: %d tx w: %d\n", mcraft->txts->tx_height, mcraft->txts->tx_width);
    tx_index = get_tx_index(ray->direction);
	scale = vector.y * mcraft->ll - (WIN_H * mcraft->camera_h) * mcraft->ll / 2
		+ ray->h * mcraft->ll / 2;
	printf("debug: scale: %d\n", scale);
	vector.tex_y = ((scale * mcraft->txts->tx_height) / ray->h) / mcraft->ll;
	img_pos = vector.y * mcraft->ll + vector.x * (mcraft->bpp / 8);
	tx_pos = vector.tex_y * mcraft->ll + vector.tex_x * (mcraft->bpp / 8);
    printf("debug: tex_x: %d tex_y: %d\n", vector.tex_x, vector.tex_y);
    printf("debug: img_pos: %d tx_pos: %d\n", img_pos, tx_pos);
	*(unsigned int *)(mcraft->img_addr
			+ img_pos) = *(unsigned int *)(mcraft->txts->data[tx_index]
			+ tx_pos);
}

void	pixel_on_img(int rgb, int direction, t_pos pos, t_mcraft *mcraft)
{
	int	r;
	int	g;
	int	b;
	int	tx_index;

	tx_index = get_tx_index(direction);
	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	mcraft->txts->data[tx_index][pos.y * mcraft->ll + pos.x * mcraft->bpp
		/ 8] = b;
	mcraft->txts->data[tx_index][pos.y * mcraft->ll + pos.x * mcraft->bpp / 8
		+ 1] = g;
	mcraft->txts->data[tx_index][pos.y * mcraft->ll + pos.x * mcraft->bpp / 8
		+ 2] = r;
}

void	paint_texture_line(t_mcraft *mcraft, t_ray *ray, t_vector vector)
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
            texture_on_img(mcraft, ray, vector);
			y++;
		}
	}
}

void	paint_line(t_mcraft *mcraft, t_vector vector, int rgb, int direction)
{
	int		y;
	int		y_max;
	t_pos	pos;

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
	pos.x = vector.x;
	if (y >= 0)
	{
		while (y < y_max)
		{
	        pos.y = y;
			pixel_on_img(rgb, direction, pos, mcraft);
			y++;
		}
	}
}

void	draw_ray(t_mcraft *mcraft, t_ray *ray)
{
	t_vector	vector;
	double		wall_x;

    if (ray->direction == WEST || ray->direction == EAST)
		wall_x = mcraft->gamer->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = mcraft->gamer->x + ray->perp_wall_dist * ray->ray_dir_x;
    vector.x = ray->curr_x;
	vector.y0 = 0; // reset vector to start at top pixel
	vector.y1 = ray->draw_start;
	vector.tex_x = (int)(wall_x * (double)(mcraft->txts->tx_width));
    vector.tex_y = 0;
    // reset vector end to end at the beginning pixel
	paint_line(mcraft, vector, mcraft->txts->ceiling_color, ray->direction);
	vector.y0 = ray->draw_start;
	vector.y1 = ray->draw_end;
	paint_texture_line(mcraft, ray, vector);
	vector.y0 = ray->draw_end; // reset vector to start at end pixel of texture
	vector.y1 = WIN_H;         // reset vector to end at the bottom pixel
	paint_line(mcraft, vector, mcraft->txts->floor_color, ray->direction);
}

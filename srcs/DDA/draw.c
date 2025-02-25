/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:18:57 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/25 19:08:07 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_on_img(t_mcraft *mcraft, t_vector vector, t_img *tx_data)
{
	int	color;
	int	offset;

	if (vector.tex_x < 0)
		vector.tex_x = 0;
	if (vector.tex_x >= tx_data->w)
		vector.tex_x = tx_data->w - 1;
	vector.tex_y = (int)(((vector.y * 2 - mcraft->h + vector.h)
				* tx_data->h) / vector.h / 2);
	if (vector.tex_y < 0)
		vector.tex_x = 0;
	if (vector.tex_y >= tx_data->h)
		vector.tex_y = tx_data->h - 1;
	offset = (vector.tex_y * tx_data->w + vector.tex_x) * 4;
	if (offset < 0 || offset >= tx_data->w * tx_data->h * 4)
		return ;
	color = *(unsigned int *)(tx_data->data + offset);
	draw_pixel(mcraft, vector.x, vector.y, color);
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
			draw_pixel(mcraft, vector.x, y, rgb);
			y++;
		}
	}
}

void	paint_texture_line(t_mcraft *mcraft, t_ray *ray, t_vector vector)
{
	int		y;
	int		y_max;
	t_img	*tx_data;

	tx_data = get_tx_data(get_tx_index(ray), mcraft->txts);
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

void	draw_vector(t_mcraft *mcraft, t_ray *ray, t_pos map_pos, int x)
{
	t_vector	vector;

	setup_vector(mcraft, ray, &vector, x);
	if (mcraft->map->grid[map_pos.y][map_pos.x] == WALL)
		paint_texture_line(mcraft, ray, vector);
	vector.y0 = 0;
	vector.y1 = -vector.h / 2 + mcraft->h / 2;
	if (vector.y0 < 0)
		vector.y0 = 0;
	paint_line(mcraft, vector, mcraft->txts->ceiling_color);
	vector.y0 = mcraft->h;
	vector.y1 = vector.h / 2 + mcraft->h / 2;
	if (vector.y1 > mcraft->h)
		vector.y1 = mcraft->h;
	paint_line(mcraft, vector, mcraft->txts->floor_color);
}

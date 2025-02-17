/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:18:57 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/16 23:52:51 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_on_img(t_mcraft *mcraft, t_vector vector, char *tx_data)
{
    int color;
	int offset;

    vector.tex_y = ((vector.y - vector.y0) * mcraft->txts->tx_height) / vector.h;
    offset = (vector.tex_y * mcraft->txts->tx_width + vector.tex_x) * 4;
    printf("tex x: %d\n", vector.tex_x);
    printf("tex y: %d, offset: %d, tx height: %d\n", vector.tex_y, offset, mcraft->txts->tx_height);
    color = *(int *)(tx_data + offset);
    printf("color: %d (0x%08X) tx_data: %s\n", color, color, tx_data);
    pixel_on_img(mcraft, color, vector.x, vector.y);
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
			//pixel_on_img(mcraft, rgb, vector.x, y);
			draw_pixel(mcraft, vector.x, y, rgb);
			y++;
		}
	}
}

void	paint_texture_line(t_mcraft *mcraft, t_ray *ray, t_vector vector)
{
	int		y;
	int		y_max;
	char	*tx_data;

	tx_data = get_tx_data(get_tx_index(ray->direction), mcraft->txts);
	printf("tx_data: %s\n", tx_data);
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
	printf("y: %d, y max: %d\n", y, y_max);
	if (y >= 0)
	{
		while (y < y_max)
		{
			vector.y = y;
			printf("vector y: %d\n", vector.y);
			texture_on_img(mcraft, vector, tx_data);
			y++;
		}
	}
    sleep(2);
}

void pixel_on_img(t_mcraft *mcraft, int rgb, int x, int y)
{
    int offset = y * mcraft->txts->ll + x * 4;
    if (offset < 0 || offset + 3 >= mcraft->h * mcraft->ll)
        exit_err("Invalid offset.");
    printf("Setting pixel at offset: %d, x: %d, y: %d, rgb: %d\n", offset, x, y, rgb);
    mcraft->img_addr[offset] = (rgb & 0xFF);         // Blue
    mcraft->img_addr[offset + 1] = (rgb >> 8) & 0xFF; // Green
    mcraft->img_addr[offset + 2] = (rgb >> 16) & 0xFF; // Red
    mcraft->img_addr[offset + 3] = (rgb >> 24) & 0xFF; // Alpha
    printf("img addr at offset %d: %d\n", offset, mcraft->img_addr[offset]);
}

void	draw_vector(t_mcraft *mcraft, t_ray *ray, t_pos map_pos, int x)
{
	t_vector	vector;

	(void)map_pos;
    setup_vector(mcraft, ray, &vector, x);
	// if (mcraft->map->grid[map_pos.y][map_pos.x] == WALL)
	// 	paint_texture_line(mcraft, ray, vector);
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
}

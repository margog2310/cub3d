/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:18:57 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/15 19:02:01 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	*init_vector(t_ray *ray)
{
	t_vector	*vector;

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

void	paint_line(t_mcraft *mcraft, t_vector *vector, int rgb)
{
	int	y;
	int	y_max;

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

void	texture_on_img(t_mcraft *mcraft, t_ray *ray, t_vector vector)
{
	int		scale;
	int		tx_pos;
	int		img_pos;
	int		tx_size;
	int		img_size;
	char	*tx_index;

	tx_index = get_tx_index(ray->direction);
	scale = vector.y * mcraft->ll - (mcraft->h * mcraft->camera_h) * mcraft->ll
		/ 2 + vector.h * mcraft->ll / 2;
	vector.tex_y = ((scale * mcraft->txts->tx_height) / vector.h) / mcraft->ll;
	img_pos = vector.y * mcraft->ll + vector.tex_x * (mcraft->bpp / 8);
	tx_pos = vector.tex_y * mcraft->ll + vector.tex_x * (mcraft->bpp / 8);
	img_size = mcraft->w * mcraft->h * (mcraft->bpp / 8);
	tx_size = mcraft->txts->tx_width * mcraft->txts->tx_height * (mcraft->bpp
			/ 8);
	if (img_pos >= 0 && img_pos < img_size && tx_pos >= 0 && tx_pos < tx_size)
		*(unsigned int *)(mcraft->img_addr
				+ img_pos) = *(unsigned int *)(get_tx_data(tx_index,
					mcraft->txts) + tx_pos);
}

int	get_texture_color(t_mcraft *mcraft, t_txts *txts, int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0 || tex_x >= txts->tx_width || tex_y < 0
		|| tex_y >= txts->tx_height)
		return (0);
	color = *(unsigned int *)(get_tx_data(get_tx_index(mcraft->gamer->direction),
				txts) + (tex_y * txts->tx_width + tex_x) * (mcraft->bpp / 8));
	return (color);
}

void	draw_ray(t_mcraft *mcraft, t_ray *ray)
{
	t_vector *vector;
	double wall_x;

	wall_x = 0.0;
	vector = init_vector(ray);
	if (ray->direction == WEST || ray->direction == EAST)
		wall_x = mcraft->gamer->y * BLOCK + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		wall_x = mcraft->gamer->x * BLOCK + ray->perp_wall_dist
			* ray->ray_dir_x;
	vector->tex_x = (int)(wall_x * 64.0);
	paint_line(mcraft, vector, mcraft->txts->ceiling_color);
}
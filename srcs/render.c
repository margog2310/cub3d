/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:57:12 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 14:59:45 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_mcraft *mcraft, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < mcraft->w && y >= 0 && y < mcraft->h)
	{
		dst = mcraft->img_addr + (y * mcraft->ll + x * (mcraft->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_tile(t_mcraft *mcraft, t_pos start, int tile_size, int color)
{
	int	y;
	int	x;

	y = start.y;
	while (y < start.y + tile_size - 1)
	{
		x = start.x;
		while (x < start.x + tile_size - 1)
		{
			draw_pixel(mcraft, x, y, color);
			x++;
		}
		y++;
	}
}

void	player_position(t_mcraft *mcraft)
{
	t_gamer		*gamer;
	static int	frame_count;

	gamer = mcraft->gamer;
	frame_count = 0;
	if (frame_count % 60 == 0)
		ft_printf("Player pos: x=%d, y=%d\n", (int)gamer->x, (int)gamer->y);
	frame_count++;
}

void	update_player_angle(t_mcraft *mcraft)
{
	mcraft->gamer->dir_x = cos(mcraft->gamer->angle);
	mcraft->gamer->dir_y = sin(mcraft->gamer->angle);
	mcraft->plane_x = -mcraft->gamer->dir_y * PLANE_DIST;
	mcraft->plane_y = mcraft->gamer->dir_x * PLANE_DIST;
}

int	render_img(t_mcraft *mcraft)
{
	ft_bzero(mcraft->img_addr, mcraft->h * mcraft->ll);
	update_player_angle(mcraft);
	dda(mcraft);
	minimap(mcraft);
	draw_crosshairs(mcraft, BLACK);
	mlx_put_image_to_window(mcraft->mlx, mcraft->win, mcraft->img, 0, 0);
	return (0);
}

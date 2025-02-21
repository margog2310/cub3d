/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:57:12 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/21 20:26:15 by mganchev         ###   ########.fr       */
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

int	colors(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (free_array(rgb), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

void	draw_tile(t_mcraft *mcraft, int start_x, int start_y, int tile_size,
		int color)
{
	int	y;
	int	x;

	y = start_y;
	while (y < start_y + tile_size - 1)
	{
		x = start_x;
		while (x < start_x + tile_size - 1)
		{
			draw_pixel(mcraft, x, y, color);
			x++;
		}
		y++;
	}
}

void	player_position(t_mcraft *mcraft) // temp tester function
{
	t_gamer *gamer;
	static int frame_count;

	gamer = mcraft->gamer;
	frame_count = 0;
	if (frame_count % 60 == 0)
		ft_printf("Player pos: x=%d, y=%d\n", (int)gamer->x, (int)gamer->y);
	frame_count++;
}

void	update_player_angle(t_mcraft *mcraft, double angle)
{
	mcraft->gamer->angle += angle;
	if (mcraft->gamer->angle < 0)
		mcraft->gamer->angle += 2 * PI;
	if (mcraft->gamer->angle >=  2 * PI)
		mcraft->gamer->angle -= 2 * PI;
	mcraft->gamer->dir_x = cos(mcraft->gamer->angle);
    mcraft->gamer->dir_y = sin(mcraft->gamer->angle);
    mcraft->plane_x = -mcraft->gamer->dir_y * PLANE_DIST;
    mcraft->plane_y = mcraft->gamer->dir_x * PLANE_DIST;
}

int	render_img(t_mcraft *mcraft)
{
	mcraft->plane_x = -mcraft->gamer->dir_y * PLANE_DIST;
    mcraft->plane_y = mcraft->gamer->dir_x * PLANE_DIST;
	//update_player_angle(mcraft, mcraft->gamer->angle);
	ft_bzero(mcraft->img_addr, mcraft->h * mcraft->ll);
	// need to update texture coordinates based on player movement
	minimap(mcraft);
	dda(mcraft);
	// player_position(mcraft);
	//win_bk(mcraft);
	draw_crosshairs(mcraft, BLACK);
	mlx_put_image_to_window(mcraft->mlx, mcraft->win, mcraft->img, 0, 0);
	return (0);
}

void	draw_crosshairs(t_mcraft *mcraft, int color)
{
	int	mid_x;
	int	mid_y;
	int	len;
	int	x;
	int	y;

	mid_x = WIN_W / 2;
	mid_y = WIN_H / 2;
	len = 10;
	x = mid_x - len;
	while (x <= mid_x + len)
	{
		draw_pixel(mcraft, x, mid_y, color);
		x++;
	}
	y = mid_y - len;
	while (y <= mid_y + len)
	{
		draw_pixel(mcraft, mid_x, y, color);
		y++;
	}
}

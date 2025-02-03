/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:57:12 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/03 22:23:40 by ssottori         ###   ########.fr       */
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
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

int	render_img(t_mcraft *mcraft)
{
	static int	frame_count;

	frame_count = 0;
	ft_bzero(mcraft->img_addr, mcraft->h * mcraft->ll);
	move_player(mcraft);
	if (frame_count % 60 == 0)
		printf("Player pos: x=%d, y=%d\n", (int)mcraft->gamer.x, (int)mcraft->gamer.y);
	frame_count++;
	win_bk(mcraft);
	minimap(mcraft);
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

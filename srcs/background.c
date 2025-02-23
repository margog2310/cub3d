/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:43:42 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/23 03:10:45 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sky(t_mcraft *mcraft)
{
	int	x;
	int	y;

	y = 0;
	while (y < mcraft->h / 2)
	{
		x = 0;
		while (x < mcraft->w)
		{
			draw_pixel(mcraft, x, y, LIGHT_GREY);
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_mcraft *mcraft)
{
	int	x;
	int	y;
	int	y_off;

	y_off = (int)mcraft->gamer->y;
	y = mcraft->h / 2 + y_off;
	while (y < mcraft->h + y_off)
	{
		x = 0;
		while (x < mcraft->w)
		{
			draw_pixel(mcraft, x, y - y_off, DARK_GREY);
			x++;
		}
		y++;
	}
}

void	win_bk(t_mcraft *mcraft)
{
	draw_sky(mcraft);
	draw_floor(mcraft);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:02:33 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/29 15:34:13 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// just testing stuff, and playing around with maths

void	draw_square(int x, int y, int size, int color, t_mcraft *mcraft)
{
	for(int i = 0; i < size; i++)
		draw_pixel( mcraft, x + i, y, color);
	for(int i = 0; i < size; i++)
		draw_pixel( mcraft, x, y + i, color);
	for(int i = 0; i < size; i++)
		draw_pixel( mcraft, x + size, y + i, color);
	for(int i = 0; i < size; i++)
		draw_pixel(mcraft, x + i, y + size, color);
}

void	move_player(t_mcraft *mcraft)
{
	t_gamer	*gamer = &mcraft->gamer;
	
	float	cos_angle = cos(gamer->angle);
	float	sin_angle = sin(gamer->angle);

	if (gamer->rot_l)
		gamer->angle -= R_SPEED;
	if (gamer->rot_r)
		gamer->angle += R_SPEED;
	if (gamer->angle > 2 * PI)
		gamer->angle = 0;
	if (gamer->angle < 0)
		gamer->angle = 2 * PI;

	if (gamer->k_up)
	{
		gamer->x += cos_angle * P_SPEED;
		gamer->y += sin_angle * P_SPEED;
	}
	if (gamer->k_down)
	{
		gamer->x -= cos_angle * P_SPEED;
		gamer->y -= sin_angle * P_SPEED;
	}
	if (gamer->k_left)
	{
		gamer->x += sin_angle * P_SPEED;
		gamer->y -= cos_angle * P_SPEED;
	}
	if (gamer->k_right)
	{
		gamer->x -= sin_angle * P_SPEED;
		gamer->y += cos_angle * P_SPEED;
	}
}
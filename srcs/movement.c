/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 04:25:32 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/05 02:45:32 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_mcraft *mcraft, t_gamer *gamer, float cos_a, float sin_a)
{
	float	new_x;
	float	new_y;

	if (gamer->k_up)
	{
		new_x = gamer->x + cos_a * P_SPEED; //horizontal
		if (!is_wall(mcraft, new_x, gamer->y))
			gamer->x = new_x;
		new_y = gamer->y - sin_a * P_SPEED; //vertical
		if (!is_wall(mcraft, gamer->x, new_y)) //zomethin wrong here
			gamer->y = new_y;
	}
}

void	move_down(t_mcraft *mcraft, t_gamer *gamer, float cos_a, float sin_a)
{
	float	new_x;
	float	new_y;

	if (gamer->k_down)
	{
		new_x = gamer->x - cos_a * P_SPEED;
		if (!is_wall(mcraft, new_x, gamer->y)) //wrong wayyy :(
			gamer->x = new_x;
		new_y = gamer->y + sin_a * P_SPEED;
		if (!is_wall(mcraft, gamer->x, new_y))
			gamer->y = new_y;
	}
}

void	move_left(t_mcraft *mcraft, t_gamer *gamer, float cos_a, float sin_a)
{
	float	new_x;
	float	new_y;

	if (gamer->k_left)
	{
		new_x = gamer->x + sin_a * P_SPEED;
		if (!is_wall(mcraft, new_x, gamer->y))
			gamer->x = new_x;
		new_y = gamer->y - cos_a * P_SPEED;
		if (!is_wall(mcraft, gamer->x, new_y))
			gamer->y = new_y;
	}
}

void	move_right(t_mcraft *mcraft, t_gamer *gamer, float cos_a, float sin_a)
{
	float	new_x;
	float	new_y;

	if (gamer->k_right)
	{
		new_x = gamer->x - sin_a * P_SPEED;
		if (!is_wall(mcraft, new_x, gamer->y))
			gamer->x = new_x;
		new_y = gamer->y + cos_a * P_SPEED;
		if (!is_wall(mcraft, gamer->x, new_y))
			gamer->y = new_y;
	}
}

void	move_arrows(t_mcraft *mcraft, t_gamer *gamer, float cos_a, float sin_a) 
{
	if (gamer->k_up) //rotation movement is drifting and causing player to move diagonally...
		move_up(mcraft, gamer, cos_a, sin_a);
	if (gamer->k_down)
		move_down(mcraft, gamer, cos_a, sin_a);
	if (gamer->k_left)
		move_left(mcraft, gamer, cos_a, sin_a);
	if (gamer->k_right)
		move_right(mcraft, gamer, cos_a, sin_a);
}

void	move_player(t_mcraft *mcraft)
{
	t_gamer	*gamer;
	float	cos_a;
	float	sin_a;

	gamer = &mcraft->gamer;
	cos_a = cos(gamer->angle);
	sin_a = sin(gamer->angle);
	if (gamer->rot_l)
		gamer->angle -= R_SPEED;
	if (gamer->rot_r)
		gamer->angle += R_SPEED;
	if (gamer->angle > 2 * PI)
		gamer->angle = 0;
	if (gamer->angle < 0)
		gamer->angle = 2 * PI;
	move_arrows(mcraft, gamer, cos_a, sin_a);
}

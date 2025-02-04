/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 04:25:32 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/04 04:26:53 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void move_arrows(t_mcraft *mcraft, t_gamer *gamer, float cos_angle, float sin_angle)
{
	float new_x, new_y;

	// UP: Move forward along the direction the player is facing.
	if (gamer->k_up)
	{
		// Check horizontal movement first.
		new_x = gamer->x + cos_angle * P_SPEED;
		if (!is_wall(mcraft, new_x, gamer->y))
			gamer->x = new_x;
		
		// Then check vertical movement.
		new_y = gamer->y + sin_angle * P_SPEED;
		if (!is_wall(mcraft, gamer->x, new_y))
			gamer->y = new_y;
	}

	// DOWN: Move backward.
	if (gamer->k_down)
	{
		new_x = gamer->x - cos_angle * P_SPEED;
		if (!is_wall(mcraft, new_x, gamer->y))
			gamer->x = new_x;
		
		new_y = gamer->y - sin_angle * P_SPEED;
		if (!is_wall(mcraft, gamer->x, new_y))
			gamer->y = new_y;
	}

	// LEFT: Strafe left (move perpendicular to the facing direction).
	if (gamer->k_left)
	{
		new_x = gamer->x + sin_angle * P_SPEED;
		if (!is_wall(mcraft, new_x, gamer->y))
			gamer->x = new_x;
		
		new_y = gamer->y - cos_angle * P_SPEED;
		if (!is_wall(mcraft, gamer->x, new_y))
			gamer->y = new_y;
	}

	// RIGHT: Strafe right.
	if (gamer->k_right)
	{
		new_x = gamer->x - sin_angle * P_SPEED;
		if (!is_wall(mcraft, new_x, gamer->y))
			gamer->x = new_x;
		
		new_y = gamer->y + cos_angle * P_SPEED;
		if (!is_wall(mcraft, gamer->x, new_y))
			gamer->y = new_y;
	}
}

void	move_player(t_mcraft *mcraft)
{
	t_gamer	*gamer;
	float	cos_angle;
	float	sin_angle;

	gamer = &mcraft->gamer;
	cos_angle = cos(gamer->angle);
	sin_angle = sin(gamer->angle);
	if (gamer->rot_l)
		gamer->angle -= R_SPEED;
	if (gamer->rot_r)
		gamer->angle += R_SPEED;
	if (gamer->angle > 2 * PI)
		gamer->angle = 0;
	if (gamer->angle < 0)
		gamer->angle = 2 * PI;
	move_arrows(mcraft, gamer, cos_angle, sin_angle);
}
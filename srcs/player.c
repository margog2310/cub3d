/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:05:30 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/05 17:40:03 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_gamer *gamer)
{
	gamer->x = WIN_W / 2;
	gamer->y = WIN_H / 2;
	gamer->angle = PI / 2;
	gamer->k_up = false;
	gamer->k_down = false;
	gamer->k_right = false;
	gamer->k_left = false;
	gamer->rot_l = false;
	gamer->rot_r = false;
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:05:30 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 18:53:21 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_gamer **gamer)
{
	*gamer = malloc(sizeof(t_gamer));
	if (!(*gamer))
		exit_err("Memory allocation failed.");
	(*gamer)->angle = 0;
	(*gamer)->dir_x = cos((*gamer)->angle);
	(*gamer)->dir_y = sin((*gamer)->angle);
	(*gamer)->k_up = false;
	(*gamer)->k_down = false;
	(*gamer)->k_right = false;
	(*gamer)->k_left = false;
	(*gamer)->rot_l = false;
	(*gamer)->rot_r = false;
	(*gamer)->direction = 0;
}

void	move_player(t_mcraft *mcraft)
{
	t_gamer	*gamer;
	float	cos_a;
	float	sin_a;

	gamer = mcraft->gamer;
	cos_a = cos(gamer->angle);
	sin_a = sin(gamer->angle);
	if (gamer->rot_l)
		gamer->angle -= R_SPEED;
	if (gamer->rot_r)
		gamer->angle += R_SPEED;
	if (gamer->angle >= 2 * PI)
		gamer->angle -= 2 * PI;
	if (gamer->angle < 0)
		gamer->angle += 2 * PI;
	gamer->grid_x = (gamer->x * TILE_S) + (TILE_S / 2);
	gamer->grid_y = (gamer->y * TILE_S) + (TILE_S / 2);
	move_arrows(mcraft, gamer, cos_a, sin_a);
}

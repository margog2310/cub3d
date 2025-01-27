/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:05:30 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/26 22:34:47 by ssottori         ###   ########.fr       */
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


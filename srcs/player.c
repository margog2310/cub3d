/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:05:30 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/05 03:18:42 by ssottori         ###   ########.fr       */
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

bool	is_wall(t_mcraft *mcraft, float px, float py) //collision detection
{
	int	x;
	int	y; 

	x = (int)px / BLOCK;
	y = (int)py / BLOCK;
	if (x < 0 || x >= mcraft->map->cols
		|| y < 0 || y >= mcraft->map->rows)
		return (true);
	if (mcraft->map->grid[y][x] == '1')
		return (true);
	return (false);
}

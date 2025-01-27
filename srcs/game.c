/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:02:33 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/27 17:49:32 by ssottori         ###   ########.fr       */
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

// int	key_release(int keycode, t_gamer *gamer)
// {
// 	if (keycode == W)
// 		gamer->k_up = false;
// 	if (keycode == S)
// 		gamer->k_down = false;
// 	if (keycode == A)
// 		gamer->k_left = false;
// 	if (keycode == D)
// 		gamer->k_right = false;
// 	if (keycode == LEFT)
// 		gamer->rot_l = false;
// 	if (keycode == RIGHT)
// 		gamer->rot_r = false;
// 	return (0);
// }

// int	key_press(int keycode, t_gamer *gamer)
// {
// 	if (keycode == W)
// 		gamer->k_up = true;
// 	if (keycode == S)
// 		gamer->k_down = true;
// 	if (keycode == A)
// 		gamer->k_left = true;
// 	if (keycode == D)
// 		gamer->k_right = true;
// 	if (keycode == LEFT)
// 		gamer->rot_l = true;
// 	if (keycode == RIGHT)
// 		gamer->rot_r = true;
// 	return (0);
// }
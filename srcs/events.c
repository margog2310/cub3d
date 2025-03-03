/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:27:47 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 19:21:55 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keyhooks(t_mcraft *mcraft)
{
	mlx_hook(mcraft->win, KeyPress, KeyPressMask, keys, mcraft);
	mlx_hook(mcraft->win, KeyRelease, KeyReleaseMask, key_release, mcraft);
	mlx_hook(mcraft->win, ButtonPress, ButtonPressMask, mouse, mcraft);
	mlx_hook(mcraft->win, DestroyNotify, StructureNotifyMask, exit_win, mcraft);
	mlx_hook(mcraft->win, FocusOut, FocusChangeMask, minimize, mcraft);
	mlx_hook(mcraft->win, FocusIn, FocusChangeMask, maximize, mcraft);
}

int	keys(int keycode, t_mcraft *mcraft)
{
	t_gamer	*gamer;

	gamer = mcraft->gamer;
	if (keycode == ESC)
		exit_win(mcraft);
	wads_keys(keycode, gamer);
	arrow_keys(keycode, gamer);
	move_player(mcraft);
	return (0);
}

int	wads_keys(int keycode, t_gamer *gamer)
{
	if (keycode == W)
	{
		gamer->k_up = true;
		ft_printf("W key pressed: Move forward\n");
	}
	else if (keycode == A)
	{
		gamer->k_left = true;
		ft_printf("A key pressed: Strafe left\n");
	}
	else if (keycode == S)
	{
		gamer->k_down = true;
		ft_printf("S key pressed: Move backward\n");
	}
	else if (keycode == D)
	{
		gamer->k_right = true;
		ft_printf("D key pressed: Strafe right\n");
	}
	return (0);
}

int	arrow_keys(int keycode, t_gamer *gamer)
{
	if (keycode == LEFT)
	{
		gamer->rot_l = true;
		ft_printf("Left arrow key pressed: Rotate left\n");
	}
	else if (keycode == RIGHT)
	{
		gamer->rot_r = true;
		ft_printf("Right arrow key pressed: Rotate right\n");
	}
	else if (keycode == UP)
		ft_printf("Up arrow key pressed: Look up\n");
	else if (keycode == DOWN)
		ft_printf("Down arrow key pressed: Look down\n");
	return (0);
}

int	key_release(int keycode, t_mcraft *mcraft)
{
	t_gamer	*gamer;

	gamer = mcraft->gamer;
	if (keycode == W)
		gamer->k_up = false;
	else if (keycode == S)
		gamer->k_down = false;
	else if (keycode == A)
		gamer->k_left = false;
	else if (keycode == D)
		gamer->k_right = false;
	else if (keycode == LEFT)
		gamer->rot_l = false;
	else if (keycode == RIGHT)
		gamer->rot_r = false;
	return (0);
}

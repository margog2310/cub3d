/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:27:47 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/24 03:18:22 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keyhooks(t_mcraft *mcraft)
{
	mlx_hook(mcraft->win, KeyPress, KeyPressMask, keys, mcraft);
	mlx_hook(mcraft->win, ButtonPress, ButtonPressMask, mouse, mcraft);
	mlx_hook(mcraft->win, DestroyNotify, StructureNotifyMask, exit_win, mcraft);
}

int	keys(int keycode, t_mcraft *mcraft)
{
	if (keycode == ESC)
		exit_win(mcraft);
	else if (keycode == W)
		ft_printf("W key pressed: Move forward\n");
	else if (keycode == A)
		ft_printf("A key pressed: Strafe left\n");
	else if (keycode == S)
		ft_printf("S key pressed: Move backward\n");
	else if (keycode == D)
		ft_printf("D key pressed: Strafe right\n");
	else if (keycode == LEFT)
		ft_printf("Left arrow key pressed: Rotate left\n");
	else if (keycode == RIGHT)
		ft_printf("Right arrow key pressed: Rotate right\n");
	else if (keycode == UP)
		ft_printf("Up arrow key pressed: Look up\n");
	else if (keycode == DOWN)
		ft_printf("Down arrow key pressed: Look down\n");
	return (0);
}

int	mouse(int click, int x, int y)
{
	ft_printf("Mouse click %d at (%d, %d)\n", click, x, y); //need to fix mouse click x and y coordinates wrong
	return (0);
}

int	exit_win(t_mcraft *mcraft)
{
	if (mcraft->img)
		mlx_destroy_image(mcraft->mlx, mcraft->img);
	if (mcraft->win)
		mlx_destroy_window(mcraft->mlx, mcraft->win);
	exit(0);
}
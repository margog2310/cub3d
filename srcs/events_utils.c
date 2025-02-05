/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:43:17 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/05 01:43:28 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse(t_mcraft *mcraft, int click, int x, int y)
{
	(void)mcraft;
	ft_printf("Mouse click %d at (%d, %d)\n", click, x, y); //need to fix mouse click x and y coordinates wrong
	return (0);
}

int	minimize(t_mcraft *mcraft)
{
	(void)mcraft;
	ft_printf("Window minimized. Pausing rendering...\n");
	return (0);
}

int	maximize(t_mcraft *mcraft)
{
	ft_printf("Window maximized. Resuming rendering...\n");
	mlx_put_image_to_window(mcraft->mlx, mcraft->win, mcraft->img, 0, 0);
	return (0);
}
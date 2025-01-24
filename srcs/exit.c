/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:37:56 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/24 05:53:48 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_win(t_mcraft *mcraft)
{
	if (mcraft->img)
		mlx_destroy_image(mcraft->mlx, mcraft->img);
	if (mcraft->win)
		mlx_destroy_window(mcraft->mlx, mcraft->win);
	exit(0);
}

void	cleanup_game(t_mcraft *mcraft)
{
	mlx_destroy_window(mcraft->mlx, mcraft->win);
	mlx_destroy_image(mcraft->mlx, mcraft->img);
	if (mcraft->map)
		cleanup_map(mcraft->map);
	free(mcraft);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (map->grid[i])
			free(map->grid[i++]);
		free(map->grid);
	}
	free(map);
}
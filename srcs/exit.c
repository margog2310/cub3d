/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:37:56 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/21 21:47:39 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_err(char *str, t_mcraft *mcraft)
{
	cleanup_game(mcraft);
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	exit(EXIT_FAILURE);
}

int	exit_win(t_mcraft *mcraft)
{
	cleanup_game(mcraft);
	ft_printf("Window closed. Exiting game...\n");
	exit(EXIT_SUCCESS);
}

void	cleanup_txts(t_mcraft *mcraft)
{
	if (mcraft->txts)
	{
		mlx_destroy_image(mcraft->mlx, mcraft->txts->tx_n_img);
		mlx_destroy_image(mcraft->mlx, mcraft->txts->tx_s_img);
		mlx_destroy_image(mcraft->mlx, mcraft->txts->tx_e_img);
		mlx_destroy_image(mcraft->mlx, mcraft->txts->tx_w_img);
		free(mcraft->txts->tx_n);
		free(mcraft->txts->tx_s);
		free(mcraft->txts->tx_e);
		free(mcraft->txts->tx_w);
		free(mcraft->txts->floor_id);
		free(mcraft->txts->ceiling_id);
		free(mcraft->txts);
	}
}

int	cleanup_game(t_mcraft *mcraft)
{
	if (mcraft)
	{	
		if (mcraft->img)
			mlx_destroy_image(mcraft->mlx, mcraft->img);
		if (mcraft->map)
		{
			if (mcraft->map->grid)
				free_grid(mcraft->map->grid, mcraft->map->rows);
			free(mcraft->map);
		}
		if (mcraft->txts)
			cleanup_txts(mcraft);
		if (mcraft->gamer)
			free(mcraft->gamer);
		if (mcraft->win)
			mlx_destroy_window(mcraft->mlx, mcraft->win);
		if (mcraft->mlx)
		{
			mlx_destroy_display(mcraft->mlx);
			free(mcraft->mlx);
		}
		free(mcraft);
	}
	return (0);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

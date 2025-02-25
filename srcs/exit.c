/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:37:56 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 17:42:00 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_err(char *str)
{
	cleanup_game(get_mcraft(NULL));
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	exit(EXIT_FAILURE);
}

int	exit_win(t_mcraft *mcraft)
{
	cleanup_game(mcraft);
	ft_printf("Window closed. Exiting game... THANKS FOR PLAYING!\n");
	exit(EXIT_SUCCESS);
}

void	free_tx(t_mcraft *mcraft, t_img *tx)
{
	if (tx->img)
		mlx_destroy_image(mcraft->mlx, tx->img);
	if (tx->path)
		free(tx->path);
	free(tx);
}

void	cleanup_txts(t_mcraft *mcraft)
{
	if (mcraft->txts)
	{
		if (mcraft->txts->tx_n)
			free_tx(mcraft, mcraft->txts->tx_n);
		if (mcraft->txts->tx_s)
			free_tx(mcraft, mcraft->txts->tx_s);
		if (mcraft->txts->tx_e)
			free_tx(mcraft, mcraft->txts->tx_e);
		if (mcraft->txts->tx_w)
			free_tx(mcraft, mcraft->txts->tx_w);
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

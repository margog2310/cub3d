/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:37:35 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/24 06:42:15 by margo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx(t_mcraft *mcraft)
{
	mcraft->mlx = mlx_init();
	if (!mcraft->mlx)
		exit_err("MLX init failed.");
}

void	init_window(t_mcraft *mcraft, int w, int h)
{
	mcraft->w = w;
	mcraft->h = h;
	mcraft->win = mlx_new_window(mcraft->mlx, w, h, "Cub3D Babyyyy");
	if (!mcraft->win)
	{
		ft_printf("Error: Window creation failed.\n");
		mlx_destroy_display(mcraft->mlx);
		free(mcraft->mlx);
		exit(EXIT_FAILURE);
	}
}

static void	init_img(t_mcraft *mcraft)
{
	mcraft->img = mlx_new_image(mcraft->mlx, mcraft->w, mcraft->h);
	if (!mcraft->img)
	{
		ft_printf("Error: Image creation failed.\n");
		mlx_destroy_window(mcraft->mlx, mcraft->win);
		mlx_destroy_display(mcraft->mlx);
		free(mcraft->mlx);
		exit(EXIT_FAILURE);
	}
	mcraft->img_addr = mlx_get_data_addr(mcraft->img, &mcraft->bpp, &mcraft->ll,
			&mcraft->end);
}

void	init_textures(t_mcraft *mcraft)
{
	mcraft->txts = malloc(sizeof(t_txts));
	if (!mcraft->txts)
		exit_err("Memory allocation failed.");
	ft_bzero(mcraft->txts, sizeof(t_txts));
	mcraft->txts->tx_n = malloc(sizeof(t_img));
	mcraft->txts->tx_s = malloc(sizeof(t_img));
	mcraft->txts->tx_w = malloc(sizeof(t_img));
	mcraft->txts->tx_e = malloc(sizeof(t_img));
	if (!mcraft->txts->tx_n || !mcraft->txts->tx_s || !mcraft->txts->tx_e || !mcraft->txts->tx_w)
		exit_err("Memory allocation failed.");
	ft_bzero(mcraft->txts->tx_n, sizeof(t_img));
	ft_bzero(mcraft->txts->tx_s, sizeof(t_img));
	ft_bzero(mcraft->txts->tx_w, sizeof(t_img));
	ft_bzero(mcraft->txts->tx_e, sizeof(t_img));
	mcraft->txts->floor_color = 0;
	mcraft->txts->ceiling_color = 0;
}

void	init_win(t_mcraft *mcraft, char **av)
{
	init_mlx(mcraft);
	init_textures(mcraft);
	init_player(&mcraft->gamer);
	if (parse(mcraft, av[1]))
		exit_err("Error: Map parsing failed.");
	init_window(mcraft, WIN_W, WIN_H);
	init_img(mcraft);
	mcraft->camera_h = mcraft->h / 2;
	mcraft->has_moved = false;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:37:35 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/10 19:49:52 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx(t_mcraft *mcraft)
{
	mcraft->mlx = mlx_init();
	if (!mcraft->mlx)
		exit_err("MLX init failed.");
}

static void	init_window(t_mcraft *mcraft, int w, int h)
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
	mcraft->img_addr = mlx_get_data_addr(mcraft->img,
			&mcraft->bpp, &mcraft->ll, &mcraft->end);
}

void	init_textures(t_mcraft *mcraft)
{
	mcraft->txts = malloc(sizeof(t_txts));
	if (!mcraft->txts)
		exit_err("Memory allocation failed.");
	mcraft->txts->floor_color = 0;
	mcraft->txts->ceiling_color = 0;
	mcraft->txts->tx_width = 0;
	mcraft->txts->tx_height = 0;
}

void	init_win(t_mcraft *mcraft, int w, int h)
{
	init_mlx(mcraft);
	init_window(mcraft, w, h);
	init_img(mcraft);
	init_textures(mcraft);
	mcraft->camera_h = 0.5;
	//printf("debug: camera: %f\n", mcraft->camera_h);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:44:09 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 19:15:27 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_mcraft *mcraft)
{
	render_img(mcraft);
	return (0);
}

int	main(int ac, char **av)
{
	t_mcraft	*mcraft;

	(void)av;
	if (ac != 2)
		exit_err("Usage: ./cub3D <map_file.cub>");
	if (!extension(av[1], ".cub"))
		exit_err("Not a .cub file.");
	mcraft = malloc(sizeof(t_mcraft));
	if (!mcraft)
		exit_err("mcraft memory allocation failed");
	ft_bzero(mcraft, sizeof(t_mcraft));
	get_mcraft(mcraft);
	init_win(mcraft, av);
	if (mcraft)
	{
		keyhooks(mcraft);
		mlx_loop_hook(mcraft->mlx, &game_loop, mcraft);
		mlx_loop(mcraft->mlx);
		exit_win(mcraft);
	}
	return (0);
}

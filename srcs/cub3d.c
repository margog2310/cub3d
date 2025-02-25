/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:44:09 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 16:21:01 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_mcraft *mcraft)
{
	render_img(mcraft);
	mcraft->has_moved = false;
	return (0);
}

int	main(int ac, char **av)
{
	t_mcraft	*mcraft;

	(void)av;
	if (ac != 2)
		exit_err("Usage: ./cub3D <map_file.cub>");
	if (!cub_extension(av[1]))
	{
		ft_printf("Error: must be a '.cub' file");
		exit(EXIT_FAILURE);
	}
	mcraft = malloc(sizeof(t_mcraft));
	if (!mcraft)
		exit_err("mcraft memory allocation failed");
	ft_bzero(mcraft, sizeof(t_mcraft));
	get_mcraft(mcraft);
	init_win(mcraft, av);
	if (mcraft)
	{
		keyhooks(mcraft);
		//render_img(mcraft);
		mlx_loop_hook(mcraft->mlx, &game_loop, mcraft);
		mlx_loop(mcraft->mlx);
		exit_win(mcraft);
	}
	return (0);
}

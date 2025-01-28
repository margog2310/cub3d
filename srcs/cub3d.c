/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:44:09 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/28 15:32:23 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_mcraft	*mcraft;

	(void)av;
	if (ac != 2)
		exit_err("Usage: ./cub3D <map_file.cub>");
	mcraft = malloc(sizeof(t_mcraft));
	if (!mcraft)
		exit_err("mcraft memory allocation failed");
	ft_bzero(mcraft, sizeof(t_mcraft));
	printf("debug: lets start\n");
		if (!parse_map(mcraft, av[1]))
		{
			ft_printf("Error: Map parsing failed.\n");
			free(mcraft);
			cleanup_game(mcraft);
			return (1);
		}
	cub_init(mcraft);
	draw_square(WIN_W / 2, WIN_H / 2, 10, 0x000000, mcraft);
	mlx_loop(mcraft->mlx);
	cleanup_game(mcraft);
	return (0);
}

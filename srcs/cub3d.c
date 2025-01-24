/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:44:09 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/24 04:41:25 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_mcraft	*mcraft;

	if (ac != 2)
	{
		ft_printf("Error: Usage: ./cub3D <map_file.cub>\n");
		return (1);
	}
	mcraft = malloc(sizeof(t_mcraft));
	if (!mcraft)
	{
		ft_printf("Error: mcraft malloc failed.\n");
		return (1);
	}
	if (!parse_map(mcraft, av[1]))
	{
		free(mcraft);
		return (1);
	}

	cub_init(mcraft);
	mlx_loop(mcraft->mlx);
	cleanup_game(mcraft);
	return (0);
}

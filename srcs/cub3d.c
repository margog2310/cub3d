/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:44:09 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/15 23:29:11 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(t_mcraft *mcraft)
{
	if (mcraft->has_changed)
	{
		render_img(mcraft);
		mcraft->has_changed = false;
	}
}

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
	cub_init(mcraft, av);
	//set_player_starting_pos(mcraft);
	//dda(mcraft);
	if (mcraft)
	{	
		mlx_loop(mcraft->mlx);
		cleanup_game(mcraft);
	}
	return (0);
}

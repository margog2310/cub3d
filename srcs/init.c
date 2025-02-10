/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:32:20 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/10 20:16:03 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Things that need to be init:
- mlx [x]
- window [x]
- events [x]
- player [x]
- map [x]
- textures
- raycasting
- game loop [x]
*/

void	cub_init(t_mcraft *mcraft, char **av)
{
	init_win(mcraft, WIN_W, WIN_H);
	init_player(&mcraft->gamer);
	if (parse(mcraft, av[1]))
	{
		free(mcraft);
		cleanup_game(mcraft);
		exit_err("Error: Map parsing failed.");
	}
	keyhooks(mcraft);
	render_img(mcraft);
	mlx_loop_hook(mcraft->mlx, render_img, mcraft);
}

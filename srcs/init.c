/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:32:20 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/05 01:44:49 by ssottori         ###   ########.fr       */
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

void	cub_init(t_mcraft *mcraft)
{
	init_win(mcraft, WIN_W, WIN_H);
	init_player(&mcraft->gamer);
	keyhooks(mcraft);
	render_img(mcraft);
	mlx_loop_hook(mcraft->mlx, render_img, mcraft);
}

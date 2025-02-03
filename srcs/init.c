/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:32:20 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/03 22:31:56 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Things that need to be init:
- mlx
- window
- events
- player
- map
- textures
- raycasting
- game loop
*/

void	cub_init(t_mcraft *mcraft)
{
	init_win(mcraft, WIN_W, WIN_H);
	init_player(&mcraft->gamer);
	keyhooks(mcraft);
	render_img(mcraft);
	mlx_loop_hook(mcraft->mlx, render_img, mcraft);
}

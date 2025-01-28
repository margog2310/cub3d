/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:32:20 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/26 22:45:20 by ssottori         ###   ########.fr       */
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
	init_player(&mcraft->gamer);
	init_win(mcraft, WIN_W, WIN_H);
	keyhooks(mcraft);
	win_bk(mcraft);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:32:20 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/13 18:05:32 by mganchev         ###   ########.fr       */
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
	init_win(mcraft, av);
	keyhooks(mcraft);
	render_img(mcraft);
	mlx_loop_hook(mcraft->mlx, render_img, mcraft);
}

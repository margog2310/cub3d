/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:08:21 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/08 19:26:52 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// return a pointer to the main struct
t_mcraft	*get_mcraft(t_mcraft *mcraft)
{
	static t_mcraft	*ptr;

	if (!mcraft)
		return (ptr);
	ptr = mcraft;
	return (mcraft);
}

void	set_player_starting_pos(t_mcraft *mcraft)
{
	t_map	*map;

	map = mcraft->map;
	mcraft->gamer->x = map->player_start_col * BLOCK + (BLOCK / 2);
	mcraft->gamer->y = map->player_start_row * BLOCK + (BLOCK / 2);
}

bool	is_wall(t_mcraft *mcraft, float px, float py) //collision detection
{
	int	x;
	int	y; 

	x = (int)px / BLOCK;
	y = (int)py / BLOCK;
	if (x < 0 || x >= mcraft->map->cols
		|| y < 0 || y >= mcraft->map->rows)
		return (true);
	if (mcraft->map->grid[y][x] == '1')
		return (true);
	return (false);
}

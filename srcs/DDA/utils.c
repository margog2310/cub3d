/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:04:33 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/13 21:06:26 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_cell_valid(t_map *map, int row, int col)
{
	return ((row >= 0) && (row < map->rows) && (col >= 0) && (col < map->cols));
}

t_pos	set_direction_vector(t_gamer *gamer)
{
	t_pos	direction;

	direction.x = 0;
	direction.y = 0;
	if (gamer->direction == NORTH)
	{
		direction.x = 0;
		direction.y = -1;
	}
	else if (gamer->direction == SOUTH)
	{
		direction.x = 0;
		direction.y = 1;
	}
	else if (gamer->direction == WEST)
	{
		direction.x = 1;
		direction.y = 0;
	}
	else if (gamer->direction == EAST)
	{
		direction.x = -1;
		direction.y = 0;
	}
	return (direction);
}

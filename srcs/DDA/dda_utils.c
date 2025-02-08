/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:01:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/08 22:34:05 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_cell_valid(t_map *map, bool **visited, int row, int col)
{
	int	rows;
	int	cols;

	rows = map->rows;
	cols = map->cols;
	return ((row >= 0) && (row < rows) && (col >= 0) && (col < cols)
		&& (!visited[row][col]));
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

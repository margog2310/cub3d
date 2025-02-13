/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:01:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/13 20:53:57 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_tx_index(int direction)
{
	if (direction == NORTH)
		return ("NO");
	else if (direction == SOUTH)
		return ("SO");
	else if (direction == EAST)
		return ("EA");
	else if (direction == WEST)
		return ("WE");
	return (NULL);
}

char	*get_tx_data(char *key, t_txts *txts)
{
	static t_txts *ptr;

	if (!txts)
	{
		if (!ft_strncmp(key, "NO", 2))
			return(ptr->tx_n_data);
		else if (!ft_strncmp(key, "SO", 2))
			return(ptr->tx_s_data);
		else if (!ft_strncmp(key, "WE", 2))
			return (ptr->tx_w_data);
		else if (!ft_strncmp(key, "EA", 2))
			return (ptr->tx_e_data);
	}
	ptr = txts;
	if (!key)
		return (NULL);
	if (!ft_strncmp(key, "NO", 2))
		return(txts->tx_n_data);
	else if (!ft_strncmp(key, "SO", 2))
		return(txts->tx_s_data);
	else if (!ft_strncmp(key, "WE", 2))
		return (txts->tx_w_data);
	else if (!ft_strncmp(key, "EA", 2))
		return (txts->tx_e_data);
	return (NULL);			
}

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

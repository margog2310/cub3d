/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:04:33 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/21 22:55:26 by mganchev         ###   ########.fr       */
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

char	*get_tx_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return ("WE");
		else
			return ("EA");
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return ("SO");
		else
			return ("NO");
	}
	return (NULL);
}

t_img	*get_tx_data(char *key, t_txts *txts)
{
	static t_txts	*ptr;

	if (!txts)
	{
		if (!ft_strncmp(key, "NO", 2))
			return (ptr->tx_n);
		else if (!ft_strncmp(key, "SO", 2))
			return (ptr->tx_s);
		else if (!ft_strncmp(key, "WE", 2))
			return (ptr->tx_w);
		else if (!ft_strncmp(key, "EA", 2))
			return (ptr->tx_e);
	}
	ptr = txts;
	if (!key)
		return (NULL);
	if (!ft_strncmp(key, "NO", 2))
		return (txts->tx_n);
	else if (!ft_strncmp(key, "SO", 2))
		return (txts->tx_s);
	else if (!ft_strncmp(key, "WE", 2))
		return (txts->tx_w);
	else if (!ft_strncmp(key, "EA", 2))
		return (txts->tx_e);
	return (NULL);
}

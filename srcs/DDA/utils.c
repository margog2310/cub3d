/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:04:33 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/15 22:47:52 by mganchev         ###   ########.fr       */
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

int	get_texture_color(t_mcraft *mcraft, t_txts *txts, int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0 || tex_x >= txts->tx_width || tex_y < 0
		|| tex_y >= txts->tx_height)
		return (0);
	color = *(unsigned int *)(get_tx_data(get_tx_index(mcraft->gamer->direction),
				txts) + (tex_y * txts->tx_width + tex_x) * (mcraft->bpp / 8));
	return (color);
}

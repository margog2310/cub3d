/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:52:08 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 19:11:47 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_symbol(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v');
}

bool	is_space_enclosed(t_map *map, int len_current, int i, int j)
{
	if (j > 0 && (map->grid[i][j - 1] != WALL && !chrsetcmp(map->grid[i][j - 1],
		WS)))
		return (false);
	if (j < len_current - 1 && (map->grid[i][j + 1] != WALL
		&& !chrsetcmp(map->grid[i][j + 1], WS)))
		return (false);
	if (i > 0 && (map->grid[i - 1][j] != WALL && !chrsetcmp(map->grid[i - 1][j],
		WS)))
		return (false);
	if (i < map->rows - 1 && (map->grid[i + 1][j] != WALL
		&& !chrsetcmp(map->grid[i + 1][j], WS)))
		return (false);
	return (true);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_longest_row(t_map *map, char *key)
{
	int	i;
	int	len;
	int	index;

	i = 0;
	len = 0;
	index = 0;
	while (i < map->rows)
	{
		if (ft_strlen(map->grid[i]) > len)
		{
			len = ft_strlen(map->grid[i]);
			index = i;
		}
		i++;
	}
	if (ft_strcmp(key, "LEN") == 0)
		return (len);
	else if (ft_strcmp(key, "INDEX") == 0)
		return (index);
	return (-1);
}

void	set_player_direction(int *direction, float *angle, char key)
{
	if (key == 'N')
	{
		*direction = NORTH;
		*angle = (float)(3 * PI / 2);
	}
	else if (key == 'S')
	{
		*direction = SOUTH;
		*angle = (float)(PI / 2);
	}
	else if (key == 'W')
	{
		*direction = WEST;
		*angle = PI;
	}
	else if (key == 'E')
	{
		*direction = EAST;
		*angle = 0.0;
	}
}

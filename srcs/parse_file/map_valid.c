/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/21 23:18:35 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	// 1. check if all symbols are valid
	// 2. check if map is surrounded by walls
	3. check that map is last in file > there could be 
	   empty lines after map but no other information
	//4. check that extension is .cub
	// 5. check that information (besides map) is separated by one or more space
	// 6. check identifiers and paths to textures are valid

	stored in 2D array, parsed top to bottom, left to right
		- if strlen(curr_row) > strlen(row_on_top)
			&& curr_col > strlen(row_on_top) -> curr char should always be 1
		- if strlen(curr_row) > strlen(row_on_bottom)
			&& curr_col > strlen(row_on_bottom)
			-> curr char should also always be 1
*/

bool	is_map_valid(t_mcraft *mcraft, t_map *map)
{
	if (!is_enclosed(map))
	{
		exit_err("Error: Map is not enclosed by walls.\n");
		return (false);
	}
	if (!symbols_valid(mcraft, map))
	{
		exit_err("Error: Invalid symbols in map.\n");
		return (false);
	}
	return (true);
}

bool	is_enclosed(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (i++ < map->rows - 1)
	{
		len = ft_strlen(map->grid[i]) - 1;
		if (i == 0 || i == map->rows)
		{
			j = -1;
			while (j++ < len - 1)
			{
				if (map->grid[i][j] != WALL)
					return (false);
			}
		}
		else
		{
			if (map->grid[i][0] != WALL || map->grid[i][len - 1] != WALL)
				return (false);
		}
	}
	return (true);
}

static bool	is_valid_symbol(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

static bool	is_player(t_gamer *gamer, char c)
{
	static int	player_count;

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		player_count++;
		if (player_count != 1)
			return (exit_err("Error: Map must have only 1 player."), false);
		set_player_direction(&gamer->direction, &gamer->angle, c);
		return (true);
	}
	return (false);
}

bool	symbols_valid(t_mcraft *mcraft, t_map *map)
{
	int	i;
	int	j;
	int	cols;

	i = -1;
	while (i++ < map->rows - 1)
	{
		j = -1;
		cols = ft_strlen(map->grid[i]) - 1;
		while (j++ < cols - 1)
		{
			skip_set(map->grid[i], IFS);
			if (!is_valid_symbol(map->grid[i][j]))
				return (false);
			if (is_player(mcraft->gamer, map->grid[i][j]))
			{
				mcraft->gamer->x = j;
				mcraft->gamer->y = i;
			}
		}
	}
	return (true);
}

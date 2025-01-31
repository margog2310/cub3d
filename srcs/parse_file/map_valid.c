/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/29 23:08:54 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	// 1. check if all symbols are valid
	// 2. check if map is surrounded by walls
	3. check that map is last in file > there could be empty lines after map but no other information
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

bool	is_map_valid(t_map *map)
{
	if (!is_enclosed(map))
	{
		ft_printf("Error: Map is not enclosed by walls.\n");
		return (false);
	}
	if (!symbols_valid(map))
	{
		ft_printf("Error: Invalid symbols in map.\n");
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
		else // Checking middle rows here
		{
			//printf("%s", map->grid[i]);
			if (map->grid[i][0] != WALL || map->grid[i][len - 1] != WALL)
				return (false);
		}
	}
	return (true);
}

bool	symbols_valid(t_map *map)
{
	int	i;
	int	j;
	int	cols;
	int	player_count;

	i = -1;
	player_count = 0;
	while (i++ < map->rows - 1)
	{
		j = 1;
		cols = ft_strlen(map->grid[i]) - 1;
		while (j++ < cols - 1)
		{
			skip_set(map->grid[i], IFS);
			if (map->grid[i][j] == START)
				player_count++;
			if (map->grid[i][j] != WALL && map->grid[i][j] != EMPTY
				&& map->grid[i][j] != START)
				return (false);
		}
	}
	if (player_count != 1) // checke theres only 1 player starting pos
		exit_err("Error: Map must have exactly one player starting position.\n");
	return (true);
}

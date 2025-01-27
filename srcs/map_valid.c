/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/27 18:52:42 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	// 1. check if all symbols are valid
	// 2. check if map is surrounded by walls
	3. check that map is last in file
	4. check that extension is .cub
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
	if (!is_enclosed(map->grid))
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

bool	is_enclosed(char **grid)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (grid[i])
	{
		len = ft_strlen(grid[i]) - 1;
		if (i == 0 || !grid[i + 1]) // Checking first and last rows bc was broken
		{
			j = 0;
			while (j < len)
			{
				if (grid[i][j] != WALL)
					return (false);
				j++;
			}
		}
		else // Checking middle rows here
		{
			if (grid[i][0] != WALL || grid[i][len - 1] != WALL)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	symbols_valid(t_map *map)
{
	int	i;
	int	j;
	int	cols;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->rows)
	{
		j = 0;
		cols = ft_strlen(map->grid[i]) - 1;
		while (j < cols)
		{
			skip_set(map->grid[i], IFS);
			if (map->grid[i][j] != WALL && map->grid[i][j] != EMPTY
				&& map->grid[i][j] != START)
				return (false);
			j++;
		}
		i++;
	}
	if (player_count != 1) // checke theres only 1 player starting pos
	{
		ft_printf("Error: Map must have exactly one player starting position.\n");
		return (false);
	}
	return (true);
}

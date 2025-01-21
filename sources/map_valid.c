/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/21 19:59:42 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	// 1. check if all symbols are valid
	// 2. check if map is surrounded by walls
	3. check that map is last in file
	4. check that extension is .cub
	5. check that information (besides map) is separated by one or more space
	6. check identifiers and paths to textures are valid

	stored in 2D array, parsed top to bottom, left to right
		- if strlen(curr_row) > strlen(row_on_top)
			&& curr_col > strlen(row_on_top) -> curr char should always be 1
		- if strlen(curr_row) > strlen(row_on_bottom)
			&& curr_col > strlen(row_on_bottom)
			-> curr char should also always be 1
*/

bool	is_enclosed(char **grid, int line_count)
{
	int	i;
	int	j;
	int	len;
	int	cmp_len;

	i = 0;
	while (grid[i])
	{
		j = 0;
		len = ft_strlen(grid[i]) - 1;
		while (j < len)
		{
			if ((grid[i - 1] && (cmp_len = ft_strlen(grid[i - 1]) - 1)
					&& len > cmp_len && j > cmp_len && grid[i][j] != WALL)
				|| (grid[i + 1] && (cmp_len = ft_strlen(grid[i + 1]) - 1)
					&& len > cmp_len && j > cmp_len && grid[i][j] != WALL))
				return (false);
			j++;
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

	i = 0;
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
	return (true);
}

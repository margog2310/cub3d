/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/25 19:11:47 by mganchev         ###   ########.fr       */
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

char	*pad_row(char *line, int len, int max_len)
{
	int	i;

	line = ft_realloc(line, len, max_len + 1);
	if (!line)
		exit_err("Memory allocation failed.");
	i = len;
	while (i < max_len)
	{
		line[i] = ' ';
		i++;
	}
	line[i] = '\0';
	return (line);
}

t_map	*pad_map(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	while (i < map->rows)
	{
		len = ft_strlen(map->grid[i]) - 1;
		if (len < map->cols)
			map->grid[i] = pad_row(map->grid[i], len, map->cols);
		i++;
	}
	return (map);
}

bool	check_top_and_bottom(t_map *map, char *line, int len, int i)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (chrsetcmp(line[j], WS))
		{
			if (!is_space_enclosed(map, len, i, j))
				return (false);
		}
		else if (line[j] != WALL)
			return (false);
		j++;
	}
	return (true);
}

bool	check_middle(t_map *map, char *line, int len, int i)
{
	int	j;
	int	end;

	j = 0;
	while (j < len && chrsetcmp(line[j], WS))
	{
		if (!is_space_enclosed(map, len, i, j))
			return (false);
		j++;
	}
	if (line[j] != WALL)
		return (false);
	end = len - 1;
	while (end > j && chrsetcmp(line[end], WS))
	{
		if (!is_space_enclosed(map, len, i, end))
			return (false);
		end--;
	}
	if (line[end] != WALL)
		return (false);
	return (true);
}

bool	is_enclosed(t_map *map)
{
	int	i;
	int	len;

	i = -1;
	map = pad_map(map);
	while (++i < map->rows)
	{
		len = ft_strlen(map->grid[i]) - 1;
		if (i == 0 || i == map->rows - 1)
		{
			if (!check_top_and_bottom(map, map->grid[i], len, i))
				return (false);
		}
		else
		{
			if (!check_middle(map, map->grid[i], len, i))
				return (false);
		}
	}
	return (true);
}

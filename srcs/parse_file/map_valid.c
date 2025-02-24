/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:52 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/24 10:32:43 by margo            ###   ########.fr       */
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

bool	is_space_enclosed(t_map *map, int len_current, int i, int j)
{
	if (j > 0 && (map->grid[i][j - 1] != WALL && map->grid[i][j - 1] != ' '))
		return (false);
	if (j < len_current - 1 && (map->grid[i][j + 1] != WALL && map->grid[i][j + 1] != ' '))
		return (false);
	if (i > 0 && (map->grid[i - 1][j] != WALL && map->grid[i - 1][j] != ' '))
			return (false);
	if (i < map->rows - 1 && (map->grid[i + 1][j] != WALL && map->grid[i + 1][j] != ' '))
		return (false);
	return (true);
}
bool	check_top_and_bottom(t_map *map, char *line, int len, int i)
{
	int j;

	j = 0;
	while(j < len)
	{
		if (line[j] == ' ')
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
	while (j < len && line[j] == ' ')
	{
		if (!is_space_enclosed(map, len, i, j))
			return (false);
		j++;	
	}
	if (line[j] != WALL)
		return (false);
	end = len - 1;
	while (end > j && line[end] == ' ')
	{
		if (!is_space_enclosed(map, len, i, j))
			return (false);
		end--;
	}
	if (line[end] != WALL)
		return(false);
	return (true);
}

bool	is_enclosed(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	while (i < map->rows)
	{
		len = ft_strlen(map->grid[i]) - 1;
		if (i == 0 || i == map->rows - 1)
		{
			if (!check_top_and_bottom(map, map->grid[i], len, i))
				return (false);
		}
		else
		{
			if(!check_middle(map, map->grid[i], len, i))
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	is_valid_symbol(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
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
				mcraft->gamer->x = (j);
				mcraft->gamer->y = (i);
				mcraft->gamer->grid_x = (j * TILE_S) + (TILE_S / 2);
				mcraft->gamer->grid_y = (i * TILE_S) + (TILE_S / 2);
			}
		}
	}
	return (true);
}

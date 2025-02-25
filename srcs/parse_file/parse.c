/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:04:25 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/25 14:54:56 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse(t_mcraft *mcraft, char *file)
{
	int	fd;
	int	row_index;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (exit_err("Failed to open file or file non-existent."), 1);
	row_index = parse_elements(mcraft, fd);
	if (!row_index)
		return (exit_err("Error parsing map or empty file"), close(fd), 1);
	if (create_textures(mcraft, mcraft->txts))
		exit_err("Failed to create textures.");
	mcraft->map = create_map(fd, get_next_line(fd), mcraft);
	if (!mcraft->map)
		return (exit_err("Invalid map."), close(fd), 1);
	close(fd);
	return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:04:25 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/25 18:36:07 by mganchev         ###   ########.fr       */
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

static bool	player_valid(t_mcraft *mcraft, t_map *map)
{
	int	i;
	int	j;
	int	len;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->rows)
	{
		j = 0;
		len = ft_strlen(map->grid[i]) - 1;
		while (j < len)
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		exit_err("Map must have only 1 player.");
	set_player_direction(&mcraft->gamer->direction, &mcraft->gamer->angle, map->grid[i][j]);
	return (true);
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
		}
	}
	player_valid(mcraft, map);
	return (true);
}

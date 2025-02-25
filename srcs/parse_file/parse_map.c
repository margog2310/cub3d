/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:42:54 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/25 17:54:33 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_map_grid(t_mcraft *mcraft, int fd, char *line)
{
	char	**grid;
	int		line_count;

	grid = NULL;
	line_count = 0;
	while (line)
	{
			grid = ft_realloc((void *)grid, line_count * sizeof(char *),
					(line_count + 1) * sizeof(char *));
			if (!grid)
				exit_err("Memory allocation failed.");
			grid[line_count] = ft_strdup(line);
			line_count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	mcraft->map->grid = grid;
	if (!mcraft->map->grid)
		exit_err("Error while parsing map.");
	mcraft->map->rows = line_count;
	mcraft->map->cols = get_longest_row(mcraft->map, "LEN");
	return (1);
}

t_map	*create_map(int fd, char *line, t_mcraft *mcraft)
{
	mcraft->map = malloc(sizeof(t_map));
	if (!mcraft->map)
		exit_err("Failed to allocate memory for map.");
	while (ft_strlen(line) <= 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!parse_map_grid(mcraft, fd, line) || !is_map_valid(mcraft, mcraft->map)
		|| !file_valid(line, fd, true))
	{
		exit_err("Failure parsing map.");
		free(line);
		close(fd);
		return (NULL);
	}
	return (mcraft->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:42:54 by ssottori          #+#    #+#             */
/*   Updated: 2025/02/04 01:14:52 by ssottori         ###   ########.fr       */
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
		if (ft_strlen(line) > 1)
		{
			printf("%s", line);
			grid = ft_realloc((void *)grid, line_count * sizeof(char *),
					(line_count + 1) * sizeof(char *));
			if (!grid)
				exit_err("Memory allocation failed.");
			grid[line_count] = line;
			line_count++;
		}
		line = get_next_line(fd);
	}
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
	if (!parse_map_grid(mcraft, fd, line) || !is_map_valid(mcraft, mcraft->map))
	{
		cleanup_map(mcraft->map);
		close(fd);
		return (NULL);
	}
	return (mcraft->map);
}

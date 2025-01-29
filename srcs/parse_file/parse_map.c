/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:42:54 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/29 15:32:03 by ssottori         ###   ########.fr       */
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
		if (ft_strlen(line) > 1) // skiping empty lines
		{
			grid = ft_realloc((void *)grid, line_count * sizeof(char *),
					(line_count + 1) * sizeof(char *)); // using builtin realloc
			if (!grid)
				exit_err("Memory allocation failed.");
			line_count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	mcraft->map->grid = grid;
	mcraft->map->cols = get_longest_row(mcraft->map, "LEN") - 1;
	mcraft->map->grid = grid;
	mcraft->map->rows = line_count;
	return (1);
}

t_map	*create_map(int fd, t_mcraft *mcraft)
{
	//int	i;
	int	row_index;
	char	*line;

	mcraft->map = malloc(sizeof(t_map));
	if (!mcraft->map)
		exit_err("Failed to allocate memory for map.");
	//i = 0;
	row_index = 0;
	line = get_next_line(fd);
	while (line)
	{
		row_index++;
		free(line);
		line = get_next_line(fd);
	}
	if (!parse_map_grid(mcraft, fd, line) || !is_map_valid(mcraft->map))
	{
		cleanup_map(mcraft->map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (mcraft->map);
}

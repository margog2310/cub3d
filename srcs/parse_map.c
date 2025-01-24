/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:42:54 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/24 06:39:07 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_textures_and_colors(t_mcraft *mcraft, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		mcraft->txts.tx_n = ft_strtrim(line + 3, " \t\n");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		mcraft->txts.tx_s = ft_strtrim(line + 3, " \t\n");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		mcraft->txts.tx_e = ft_strtrim(line + 3, " \t\n");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		mcraft->txts.tx_w = ft_strtrim(line + 3, " \t\n");
	else if (ft_strncmp(line, "F ", 2) == 0)
		mcraft->txts.floor_color = colors(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		mcraft->txts.ceiling_color = colors(line + 2);
	else
		return (0); // Not a texture or color line
	return (1);
}

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
			grid = ft_realloc(grid, line_count, line_count + 1);
			if (!grid)
			{
				ft_printf("Error: Memory allocation failed.\n");
				return (0);
			}
			grid[line_count] = ft_strdup(line);
			if (!grid[line_count])
			{
				ft_printf("Error: Memory allocation failed.\n");
				free_array(grid);
				return (0);
			}
			line_count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	mcraft->map->grid = grid;
	mcraft->map->rows = line_count;
	mcraft->map->cols = get_longest_row(grid, "LEN") - 1;
	return (1);
}

t_map	*create_map(char *file, t_mcraft *mcraft)
{
	int		fd;
	char	*line;

	mcraft->map = malloc(sizeof(t_map));
	if (!mcraft->map)
	{
		ft_printf("Error: Failed to allocate memory for map.\n");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(mcraft->map);
		ft_printf("Error: Failed to open map file.\n");
		return (NULL);
	}
	line = get_next_line(fd);
	while (line && parse_textures_and_colors(mcraft, line))
	{
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

int	parse_map(t_mcraft *mcraft, char *file)
{
	mcraft->map = create_map(file, mcraft);
	if (!mcraft->map)
	{
		ft_printf("Error: Invalid map.\n");
		return (0);
	}
	return (1);
}

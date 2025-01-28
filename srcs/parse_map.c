/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:42:54 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/28 16:48:55 by ssottori         ###   ########.fr       */
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
	{
		ft_printf("debug: ⚠️ No a texture/color line in map.\n");
		return (0);
	}
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
			grid = ft_realloc((void *)grid, line_count * sizeof(char *), (line_count + 1) * sizeof(char *)); //using builtin realloc
			if (!grid)
				exit_err("Memory allocation failed.");
			//grid[line_count] = ft_strdup(line);
			char *dup_line = ft_strdup(line);
			if (!dup_line)
			{
				ft_printf("❌ ERROR: `ft_strdup(line)` failed for line %d!", line_count);
				free_array(grid);
				return (0);
			}
			// if (!grid[line_count])
			// {
			// 	ft_printf("Error: Memory allocation failed.\n");
			// 	free_array(grid);
			// 	return (0);
			// }
			grid[line_count] = dup_line;
			line_count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (grid == NULL)
	{
		ft_printf("❌ ERROR: No map was read!\n"); //added for debugging
		return (0);
	}
	printf("debug: 🏗️ Map Grid Before get_longest_row():\n");
	for (int i = 0; i < line_count; i++)
	{
		if (!grid[i])
			ft_printf("❌ ERROR: grid[%d] is NULL! 🚨\n", i);
		else
		{
			printf("grid: %d %s\n", i, grid[i]); // diff from ft_printf.
			// ft_printf("   %d: \"%s\"\n", i, grid[i]); // diff than the printf prints (null) instead of grid data
		}
	}

	if (!mcraft->map)
	{
		printf("debug: ❌ ERROR: mcraft->map is NULL before assignment! Segfault incoming! 😭\n");
		return (0);
	}
	if (!grid)
	{
		ft_printf("debug: ❌ ERROR: `grid` is NULL before assigning to mcraft->map->grid! 🚨\n");
		return (0);
	}
	mcraft->map->grid = grid;
	//mcraft->map->cols = get_longest_row(grid, "LEN") - 1;
	int longest_row = get_longest_row(mcraft->map, "LEN");
	if (longest_row == -1)
	{
		ft_printf("❌ ERROR: get_longest_row() returned -1! 🚨\n");
		return (0);
	}
	mcraft->map->cols = longest_row - 1;
	mcraft->map->grid = grid;
	mcraft->map->rows = line_count;
	return (1);
}

t_map	*create_map(char *file, t_mcraft *mcraft)
{
	int		fd;
	char	*line;

	mcraft->map = malloc(sizeof(t_map));
	if (!mcraft->map)
		exit_err("Failed to allocate memory for map.");
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(mcraft->map);
		exit_err("Failed to open map file.");
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
		exit_err("Invalid map.\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:42:54 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/27 22:07:54 by ssottori         ###   ########.fr       */
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
	{
		ft_printf("debug: 🟠 Floor Color Input: %s", line + 2);
		mcraft->txts.floor_color = colors(line + 2);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		ft_printf("debug: 🔵 Ceiling Color Input: %s", line + 2);
		mcraft->txts.ceiling_color = colors(line + 2);
	}
	else
	{
		ft_printf("debug: ⚠️ Not a texture/color line. Stopping texture parsing.\n");
		return (0); // Not a texture or color line
	}
	return (1);
}

static int	parse_map_grid(t_mcraft *mcraft, int fd, char *line)
{
	char	**grid;
	int		line_count;

	grid = NULL;
	line_count = 0;
	printf("debug: in map grid\n");
	while (line)
	{
		printf("debug: 📄 🗺️ Reading map line: %s", line);
		if (ft_strlen(line) > 1) // skiping empty lines 
		{
			//grid = realloc(grid, line_count, line_count + 1);
			char **new_grid = realloc(grid, (line_count + 1) * sizeof(char *)); //using builtin realloc
			if (!new_grid)
			{
				ft_printf("❌ ERROR: `realloc()` failed! 🚨\n");
				free_array(grid);
				return (0);
			}
			grid = new_grid;
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
	printf("debug: finished reading map ✅\n");
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
	//mcraft->map->cols = get_longest_row(grid, "LEN") - 1;
	int longest_row = get_longest_row(grid, "LEN");
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
	printf("debug: successfully opened file ✅\n");
	line = get_next_line(fd);
	while (line && parse_textures_and_colors(mcraft, line))
	{
		ft_printf("debug: 📄 Processing Line: %s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("debug: does it move on after it doesnt find texture?\n");
	if (!parse_map_grid(mcraft, fd, line) || !is_map_valid(mcraft->map))
	{
		printf("debug: are we in here?\n");
		cleanup_map(mcraft->map);
		close(fd);
		return (NULL);
	}
	printf("debug: end of create map function\n");
	close(fd);
	return (mcraft->map);
}

int	parse_map(t_mcraft *mcraft, char *file)
{
	printf("debug: in parse map.\n");
	mcraft->map = create_map(file, mcraft);
	if (!mcraft->map)
		exit_err("Invalid map.\n");
	return (1);
}

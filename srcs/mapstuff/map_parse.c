/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:20:19 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/23 21:40:25 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	open_file(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	get_longest_row(char **grid, char *key)
{
	int i;
	int len;
	int index;

	i = 0;
	len = 0;
	while (grid[i])
	{
		if (ft_strlen(grid[i] > len))
		{
			len = ft_strlen(grid[i]);
			index = i;
		}
		i++;
	}
	if (ft_strcmp(key, "LEN") == 0)
		return (len);
	else if (ft_strcmp(key, "INDEX") == 0)
		return (index);
}
// need to read rest of file before map
char	**read_map(int fd, t_map *map)
{
	int line_count;
	char    *line;

	map->grid = NULL;
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->grid = ft_realloc((void *)map->grid, line_count, line_count + 1);
		if (!map->grid)
			return (ft_putstr_fd("Error: Memory Allocation\n", STDERR_FILENO));
		map->grid[line_count] = line;
		line_count++;
		line = get_next_line(fd);
	}
	map->rows = line_count;
	map->cols = get_longest_row(map->grid, "LEN") - 1;
	if (!is_map_valid(map))
		return (NULL);
	return (map);
}

int	close(int fd)
{
	if (close(fd) < 0)
		return (0);
	return (1);
}

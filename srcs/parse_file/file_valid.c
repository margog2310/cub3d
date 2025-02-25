/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:20:47 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/21 23:04:10 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	colour_valid(char *line, int bitmask)
{
	int			counter;
	char		*key;
	char		**nbrs;
	static int	repeat;

	if (repeat & bitmask)
		return (exit_err("Repeating colour."), false);
	counter = 0;
	key = ft_strchr(line, ',');
	nbrs = split_set(line, ",\n");
	if (!key || !nbrs)
		return (false);
	while (nbrs[counter])
	{
		if (ft_atoi(nbrs[counter]) < 0 || ft_atoi(nbrs[counter]) > 255)
			return (exit_err("Invalid RGB."), false);
		if (!is_nbrstr(nbrs[counter]))
			return (exit_err("Invalid RGB."), false);
		counter++;
	}
	if (counter != 3)
		return (exit_err("Invalid RGB."), false);
	repeat |= bitmask;
	free_array(nbrs);
	return (true);
}

bool	texture_valid(char *path, int bitmask)
{
	char		*extension;
	static int	repeat;

	extension = NULL;
	skip_set(path, IFS);
	if (path)
	{
		extension = ft_strrchr(path, '.');
		if (!extension || ft_strncmp(extension, ".xpm", 4))
			return (exit_err("Texture not an .xpm file."), false);
	}
	if (repeat & bitmask)
		return (exit_err("Repeating texture."), false);
	repeat |= bitmask;
	return (true);
}

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

bool	file_valid(char *line, int fd, bool map_read)
{
	if (map_read)
	{
		line = get_next_line(fd);
		while (line)
		{
			if (ft_strlen(line) > 0)
			{
				if (!ft_strncmp(line, "\n", 1))
					continue ;
				else
					return (false);
			}
			line = get_next_line(fd);
		}
	}
	free(line);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:20:47 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/21 20:36:04 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	colour_valid(t_mcraft *mcraft, char *line, int bitmask)
{
	int			counter;
	char		*key;
	char		**nbrs;
	static int	repeat;

	if (repeat & bitmask)
		return (exit_err("Repeating colour.", mcraft), false);
	counter = 0;
	key = ft_strchr(line, ',');
	nbrs = split_set(line, ",\n");
	if (!key || !nbrs)
		return (false);
	while (nbrs[counter])
	{
		if (ft_atoi(nbrs[counter]) < 0 || ft_atoi(nbrs[counter]) > 255)
			return (exit_err("Invalid RGB.", mcraft), false);
		if (!is_nbrstr(nbrs[counter]))
			return (exit_err("Invalid RGB.", mcraft), false);
		counter++;
	}
	if (counter != 3)
		return (exit_err("Invalid RGB.", mcraft), false);
	repeat |= bitmask;
	free_array(nbrs);
	return (true);
}

bool	texture_valid(t_mcraft *mcraft, char *path, int bitmask)
{
	char		*extension;
	static int	repeat;

	extension = NULL;
	skip_set(path, IFS);
	if (path)
	{
		extension = ft_strrchr(path, '.');
		if (!extension || ft_strncmp(extension, ".xpm", 4))
			return (exit_err("Texture not an .xpm file.", mcraft), false);
	}
	if (repeat & bitmask)
		return (exit_err("Repeating texture.", mcraft), false);
	repeat |= bitmask;
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
				if (ft_strlen(line) == 1 && ft_strncmp(line, "\n", 2))
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

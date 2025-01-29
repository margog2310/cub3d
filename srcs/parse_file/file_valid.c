/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:20:47 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/29 22:41:43 by mganchev         ###   ########.fr       */
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
		printf("debug: counter: %d\nnbr: %s\n", counter, nbrs[counter]);		
		if (ft_atoi(nbrs[counter]) < 0 || ft_atoi(nbrs[counter]) > 255)
			return (exit_err("Invalid RGB."), false);
		if (!is_nbrstr(nbrs[counter]))
			return (exit_err("Invalid RGB."), false);
		counter++;
	}
	if (counter != 3)
		return (exit_err("Invalid RGB."), false);
	repeat |= bitmask;
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

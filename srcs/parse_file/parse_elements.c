/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:56:21 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/28 23:54:08 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	TO DO:
		// 1. invalid rgb > must be 3 numbers between 0 and 255
		2. missing floor and/or ceiling colours
		3. empty file
		4. map not last element of file (first or in the middle)
		5. map or other elements missing
		6. map too small > only walls
		7. multiple players > could be different letters
		8. duplicate textures
*/

int	parse_textures_and_colors(t_mcraft *mcraft, char *line)
{
	static int	row_counter;

	if (ft_strncmp(line, "NO ", 3) == 0 && texture_valid(line + 3, 1))
		mcraft->txts.tx_n = ft_strtrim(line + 3, IFS);
	else if (ft_strncmp(line, "SO ", 3) == 0 && texture_valid(line + 3, 2))
		mcraft->txts.tx_s = ft_strtrim(line + 3, IFS);
	else if (ft_strncmp(line, "EA ", 3) == 0 && texture_valid(line + 3, 4))
		mcraft->txts.tx_e = ft_strtrim(line + 3, IFS);
	else if (ft_strncmp(line, "WE ", 3) == 0 && texture_valid(line + 3, 8))
		mcraft->txts.tx_w = ft_strtrim(line + 3, IFS);
	else if (ft_strncmp(line, "F ", 2) == 0 && colour_valid(line + 2, 1))
		mcraft->txts.floor_color = colors(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0 && colour_valid(line + 2, 2))
		mcraft->txts.ceiling_color = colors(line + 2);
	else
		exit_err("Missing map element.");
	row_counter++;
	if (row_counter > 6)
		return (0);
	return (1);
}

char	**parse_elements(t_mcraft *mcraft, int fd)
{
	int		row_index;
	char	*line;
	char	**elements;

	row_index = 0;
	elements = NULL;
	line = get_next_line(fd);
	while (line && row_index < 6)
	{
		if (ft_strlen(line) > 1)
		{
			printf("debug: line: %s\n", line);
			elements = ft_realloc((void *)elements, row_index * sizeof(char *),
					(row_index + 1) * sizeof(char *));
			if (!elements)
				exit_err("Error while allocating elements array.");
			if (!parse_textures_and_colors(mcraft, line))
				exit_err("Invalid map elements.");
			elements[row_index] = line;
			row_index++;
			line = get_next_line(fd);
		}
	}
	return (elements);
}

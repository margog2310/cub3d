/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:04:25 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/29 23:13:26 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse(t_mcraft *mcraft, char *file)
{
	int		fd;
	int	row_index;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return(exit_err("Failed to open file or file non-existent."), 1);
	row_index = parse_elements(mcraft, fd);
	if (!row_index)
		return(exit_err("Error while parsing map elements or empty file."), close(fd), 1);
	mcraft->map = create_map(fd, get_next_line(fd), mcraft);
	if (!mcraft->map)
		return (exit_err("Invalid map."), close(fd), 1);
	close(fd);
	return (0);
}
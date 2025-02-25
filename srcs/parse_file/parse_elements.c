/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:56:21 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/25 17:35:40 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	TO DO:
		// 1. invalid rgb > must be 3 numbers between 0 and 255
		//2. missing floor and/or ceiling colours
		//3. empty file
		4. map not last element of file (first or in the middle)
		//5. map or other elements missing
		6. map too small > only walls
		7. multiple players > could be different letters
		//8. duplicate textures
*/

bool	textures_valid(t_txts *txts)
{
	if (!extension(txts->tx_n->path, ".xpm"))
		return (false);
	if (!extension(txts->tx_s->path, ".xpm"))
		return (false);
	if (!extension(txts->tx_e->path, ".xpm"))
		return (false);
	if (!extension(txts->tx_w->path, ".xpm"))
		return (false);
	return (true);
}

int	parse_textures_and_colors(t_mcraft *mcraft, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && texture_valid(line + 2, 1))
		mcraft->txts->tx_n->path = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "SO", 2) == 0 && texture_valid(line + 2, 2))
		mcraft->txts->tx_s->path = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "EA", 2) == 0 && texture_valid(line + 2, 4))
		mcraft->txts->tx_e->path = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "WE", 2) == 0 && texture_valid(line + 2, 8))
		mcraft->txts->tx_w->path = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "F", 1) == 0 && colour_valid(line + 1, 1))
		mcraft->txts->floor_color = colors(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0 && colour_valid(line + 1, 2))
		mcraft->txts->ceiling_color = colors(line + 1);
	else
		exit_err("Missing map element.");
	return (1);
}

int	parse_elements(t_mcraft *mcraft, int fd)
{
	int		row_index;
	char	*line;
	char	*temp;

	row_index = 0;
	line = get_next_line(fd);
	while (line)
	{
		temp = line;
		if (ft_strlen(line) > 1)
		{
			line = remove_set(line, IFS);
			if (!parse_textures_and_colors(mcraft, line))
				return (free(line), exit_err("Invalid map elements."), -1);
			row_index++;
			free(line);
		}
		free(temp);
		if (row_index < 6)
			line = get_next_line(fd);
		else
			break ;
	}
	return (row_index);
}

int	create_textures(t_mcraft *mcraft, t_txts *txts)
{
	textures_valid(txts);
	txts->tx_n->img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_n->path,
			&txts->tx_n->w, &txts->tx_n->h);
	txts->tx_s->img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_s->path,
			&txts->tx_s->w, &txts->tx_s->h);
	txts->tx_e->img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_e->path,
			&txts->tx_e->w, &txts->tx_e->h);
	txts->tx_w->img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_w->path,
			&txts->tx_w->w, &txts->tx_w->h);
	if (!txts->tx_n->img || !txts->tx_s->img || !txts->tx_e->img
		|| !txts->tx_w->img)
		return (exit_err("Error with .xpm texture file."), 1);
	txts->tx_n->data = mlx_get_data_addr(txts->tx_n->img, &txts->tx_n->bpp,
			&txts->tx_n->ll, &txts->tx_n->end);
	txts->tx_s->data = mlx_get_data_addr(txts->tx_s->img, &txts->tx_s->bpp,
			&txts->tx_s->ll, &txts->tx_s->end);
	txts->tx_e->data = mlx_get_data_addr(txts->tx_e->img, &txts->tx_e->bpp,
			&txts->tx_e->ll, &txts->tx_e->end);
	txts->tx_w->data = mlx_get_data_addr(txts->tx_w->img, &txts->tx_w->bpp,
			&txts->tx_w->ll, &txts->tx_w->end);
	if (!txts->tx_n->data || !txts->tx_s->data || !txts->tx_e->data
		|| !txts->tx_w->data)
		return (exit_err("Failure getting data address."), 1);
	return (0);
}

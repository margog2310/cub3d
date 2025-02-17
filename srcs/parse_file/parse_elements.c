/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:56:21 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/16 22:17:32 by mganchev         ###   ########.fr       */
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

int	parse_textures_and_colors(t_mcraft *mcraft, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && texture_valid(line + 2, 1))
		mcraft->txts->tx_n = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "SO", 2) == 0 && texture_valid(line + 2, 2))
		mcraft->txts->tx_s = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "EA", 2) == 0 && texture_valid(line + 2, 4))
		mcraft->txts->tx_e = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "WE", 2) == 0 && texture_valid(line + 2, 8))
		mcraft->txts->tx_w = ft_strtrim(line + 2, IFS);
	else if (ft_strncmp(line, "F", 1) == 0 && colour_valid(line + 1, 1))
		mcraft->txts->floor_color = colors(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0 && colour_valid(line + 1, 2))
		mcraft->txts->ceiling_color = colors(line + 1);
	else
	{
		printf("%s\n", line);
		exit_err("Missing map element.");
	}
	return (1);
}

int	parse_elements(t_mcraft *mcraft, int fd)
{
	int		row_index;
	char	*line;

	row_index = 0;
	line = get_next_line(fd);
	while (line && row_index < 6)
	{
		if (ft_strlen(line) > 1)
		{
			line = remove_set(line, IFS);
			if (!parse_textures_and_colors(mcraft, line))
				exit_err("Invalid map elements.");
			row_index++;
		}
		line = get_next_line(fd);
	}
	return (row_index);
}

int	create_textures(t_mcraft *mcraft, t_txts *txts)
{
	txts->tx_n_img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_n,
			&txts->tx_width, &txts->tx_height);
	txts->tx_s_img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_s,
			&txts->tx_width, &txts->tx_height);
	txts->tx_e_img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_e,
			&txts->tx_width, &txts->tx_height);
	txts->tx_w_img = mlx_xpm_file_to_image(mcraft->mlx, txts->tx_w,
			&txts->tx_width, &txts->tx_height);
	if (!txts->tx_n_img || !txts->tx_s_img || !txts->tx_e_img
		|| !txts->tx_w_img)
		return(exit_err("Error with .xpm texture file."), 1);
	txts->tx_n_data = mlx_get_data_addr(txts->tx_n_img, &txts->bpp,
			&txts->ll, &txts->end);
	txts->tx_s_data = mlx_get_data_addr(txts->tx_s_img, &txts->bpp,
			&txts->ll, &txts->end);
	txts->tx_e_data = mlx_get_data_addr(txts->tx_e_img, &txts->bpp,
			&txts->ll, &txts->end);
	txts->tx_w_data = mlx_get_data_addr(txts->tx_w_img, &txts->bpp,
			&txts->ll, &txts->end);
	if (!txts->tx_n_data || !txts->tx_s_data || !txts->tx_e_data
		|| !txts->tx_w_data)
		return(exit_err("Failure getting data address."), 1);
	return (0);
}

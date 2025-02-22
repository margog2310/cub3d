/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:08:21 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/22 20:32:41 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// return a pointer to the main struct
t_mcraft	*get_mcraft(t_mcraft *mcraft)
{
	static t_mcraft	*ptr;

	if (!mcraft)
		return (ptr);
	ptr = mcraft;
	return (mcraft);
}

void	set_player_starting_pos(t_mcraft *mcraft)
{
	t_map	*map;

	map = mcraft->map;
	mcraft->gamer->x = map->player_start_col * BLOCK + (BLOCK / 2);
	mcraft->gamer->y = map->player_start_row * BLOCK + (BLOCK / 2);
}

bool	is_wall(t_mcraft *mcraft, float px, float py)
{
	int	x;
	int	y;

	x = (int)px;
	y = (int)py;
	printf("debug x: %d y: %d\n", x, y);
	if (x < 0 || x >= mcraft->map->cols || y < 0 || y >= mcraft->map->rows)
		return (true);
	if (mcraft->map->grid[y][x] == '1')
		return (true);
	return (false);
}

int	colors(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (free_array(rgb), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

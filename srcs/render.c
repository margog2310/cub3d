/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:57:12 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/24 05:38:06 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_mcraft *mcraft, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < mcraft->w && y >= 0 && y < mcraft->h)
	{
		dst = mcraft->img_addr + (y * mcraft->ll + x * (mcraft->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	colors(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:44:09 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/23 22:04:44 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
	t_mcraft *mcraft;
	
	mcraft = malloc(sizeof(t_mcraft));

	if (!mcraft)
	{
		ft_printf("Error: mcraft malloc failed.\n");
		return (1);
	}

	cub_init(mcraft);
	mlx_loop(mcraft->mlx);

	mlx_destroy_window(mcraft->mlx, mcraft->win);
	mlx_destroy_image(mcraft->mlx, mcraft->img);
	free(mcraft);
	return (0);

}
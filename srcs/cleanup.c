/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:43:45 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/21 20:57:09 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    cleanup(t_mcraft *mcraft)
{
    if (mcraft)
    {
        if (mcraft->map)
            cleanup_map(mcraft->map);
        if (mcraft->win)
            mlx_destroy_window(mcraft->mlx, mcraft->win);
        if (mcraft->mlx)
        {
            mlx_destroy_display(mcraft->mlx);
            free(mcraft->mlx);
        }
        free(mcraft);
    }
    exit(EXIT_SUCCESS);
}

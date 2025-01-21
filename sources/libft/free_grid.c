/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:49:32 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/21 18:53:58 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void    free_grid(char **grid, int line_count)
{
    int i;

    while (i < line_count)
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}

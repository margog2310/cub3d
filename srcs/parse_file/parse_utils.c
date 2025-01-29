/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:52:08 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/28 23:14:30 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_longest_row(t_map *map, char *key)
{
	int	i;
	int	len;
	int	index;

	i = 0;
	len = 0;
	index = 0;
	if (!map->grid)
	{
		ft_printf("debug: ❌ ERROR: get_longest_row() received NULL grid! 🚨\n");
		return (-1);
	}
	// 0 : 111
	// 1 : 101
	// 2 : 111
	//while (grid[i])
	while (i < 3) // you need to put NULL pointer at the end of the grid after the lines
	{
		if (!map->grid[i])
		{
			ft_printf("debug: ❌ ERROR: grid[%d] is NULL! 🚨\n", i);
			return (-1);
		}
		// ft_printf("🔍 Checking row %d: \"%s\"\n", i, grid[i]);
		// if (grid[i] && ft_strlen(grid[i]) > len)
		// {
		// 	len = ft_strlen(grid[i]);
		// 	index = i;
		// 	ft_printf("debug: 🔍 New longest row: %d (length: %d)\n", index, len);
		// }
		if (map->grid[i][0] == '\0')  // 🔥 NEW: Check if `grid[i]` is an empty string
			ft_printf("❌ ERROR: grid[%d] is an empty string! 🚨\n", i);

		// 🔥 NEW: Instead of `ft_strlen()`, manually check length safely
		int row_length = 0;
		while (map->grid[i][row_length] != '\0') row_length++;

		if (row_length > len)
		{
			len = row_length;
			index = i;
			ft_printf("🔍 New longest row: %d (length: %d)\n", index, len);
		}
		i++;
	}
	if (ft_strcmp(key, "LEN") == 0)
		return (len);
	else if (ft_strcmp(key, "INDEX") == 0)
		return (index);
	return (-1);
}

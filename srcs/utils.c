/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:52:08 by ssottori          #+#    #+#             */
/*   Updated: 2025/01/25 04:54:10 by ssottori         ###   ########.fr       */
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

int	get_longest_row(char **grid, char *key)
{
	int	i;
	int	len;
	int	index;

	i = 0;
	len = 0;
	index = 0;
	if (!grid)
	{
		ft_printf("debug: ❌ ERROR: get_longest_row() received NULL grid! 🚨\n");
		return (-1);
	}
	while (grid[i])
	{
		if (!grid[i])
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
		if (grid[i][0] == '\0')  // 🔥 NEW: Check if `grid[i]` is an empty string
		{
			ft_printf("❌ ERROR: grid[%d] is an empty string! 🚨\n", i);
		}

		// 🔥 NEW: Instead of `ft_strlen()`, manually check length safely
		int row_length = 0;
		while (grid[i][row_length] != '\0') row_length++;

		if (row_length > len)
		{
			len = row_length;
			index = i;
			ft_printf("🔍 New longest row: %d (length: %d)\n", index, len);
		}
		printf("debug: commented out strlen\n");
		i++;
	}
	ft_printf("debug: ✅ Exiting get_longest_row(): longest length = %d, longest row = %d\n", len, index);
	if (ft_strcmp(key, "LEN") == 0)
		return (len);
	else if (ft_strcmp(key, "INDEX") == 0)
		return (index);
	return (-1);
}
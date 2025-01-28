/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:25:47 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/22 21:35:07 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_mcraft	*create_game(char *file_path)
{
	t_mcraft	*mcraft;

	mcraft = malloc(sizeof(t_mcraft));
	if (!mcraft)
		return (NULL);
	mcraft->map = create_map(file_path);
	if (!mcraft->map)
	{
		cleanup_map(mcraft->map);
		return (ft_printf("Error: Invalid Map.\n"), NULL);
	}
	mcraft->mlx = mlx_init();
	if (!mcraft->mlx)
		return (free(mcraft), NULL);
	mcraft->file_path = file_path;
	return (mcraft);
}

int	main(int argc, char **argv)
{
	char *extension;
	t_mcraft *mcraft;

	if (argc == 2)
	{
		extension = ft_strchr(argv[1], ".");
		if (!extension || ft_strncmp(extension, ".cub",
				(size_t)ft_strlen(extension) != 0))
		{
			ft_printf("Error: Invalid map file.\n");
			return (1);
		}
		mcraft = create_game(argv[1]);
		if (mcraft)
		{
			mlx_hook(mcraft->win, KeyPress, KeyPressMask, handle_input, mcraft);
			mlx_loop(mcraft->mlx);
		}
	}
}
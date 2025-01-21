/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:16:58 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/21 23:27:02 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/include/libft.h"
# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define IFS " \t\n"

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define EMPTY '0'
# define WALL '1'
# define START 'N'

typedef struct s_vector
{
	int		x;
	int		y;
}			t_vector;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
}			t_map;

typedef struct s_mcraft
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
    char    *file_path;
	t_map	*map;
}			t_mcraft;

#endif
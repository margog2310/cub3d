/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:16:58 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/24 03:16:05 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


/* ========== INCLUDES ========== */
# include "../srcs/libft/include/libft.h"
# include "../srcs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdbool.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* ========== CONSTANTS ========== */
# define IFS " \t\n"

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 111
# define DOWN 116

# define EMPTY '0'
# define WALL '1'
# define START 'N'

# define SKY 0x87CEEB
# define FLOOR 0x57983B

/* ========== STRUCTS ========== */
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

	void	*img;
	char	*img_addr;
	int		bpp;
	int		ll; //line length
	int		end; //endian
}			t_mcraft;

/* ========== FUNCTIONS ========== */

/* ----- Initialization ----- */
void	cub_init(t_mcraft *mcraft);
void	init_win(t_mcraft *mcraft, int w, int h);
void	win_bk(t_mcraft *mcraft);

/* ----- Event Handling ----- */
void	keyhooks(t_mcraft *mcraft);
int		keys(int keycode, t_mcraft *mcraft);
int		mouse(int click, int x, int y);
int		exit_win(t_mcraft *mcraft);

void	draw_pixel(t_mcraft *mcraft, int x, int y, int color);

//Margos
// t_mcraft	*create_game(char *file_path);
// int open_file(char *path);
// int get_longest_row(char **grid, char *key);
// char	**read_map(int fd, t_map *map);
// int close(int fd);
// bool	is_enclosed(char **grid, int line_count);
// bool	symbols_valid(t_map *map);

#endif
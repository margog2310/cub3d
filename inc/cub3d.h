/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:16:58 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/27 17:29:42 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


/* ========== INCLUDES ========== */
# include "../libs/libft/include/libft.h"
# include "../libs/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>

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
# define M 109

# define EMPTY '0'
# define WALL '1'
# define START 'N'

# define SKY 0x87CEEB
# define FLOOR 0x57983B

# define TX_W 64
# define TX_H 64
# define WIN_W 800
# define WIN_H 600

# define PI 3.14159265359
# define BLOCK 64

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

typedef struct t_txts
{
	// Texture paths
	char	*tx_n;
	char	*tx_s;
	char	*tx_e;
	char	*tx_w;

	void	*tx_n_img;
	void	*tx_s_img;
	void	*tx_e_img;
	void	*tx_w_img;
	
	int		tx_width;
	int		tx_height;

	int		floor_color;
	int		ceiling_color;
}			t_txts;

typedef struct s_gamer
{
	float	x;
	float	y;
	float	angle;

	bool	k_up; //key_up
	bool	k_down;
	bool	k_left;
	bool	k_right;

	bool	rot_l;
	bool	rot_r;
}	t_gamer;

typedef struct s_mcraft
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	char	*file_path;
	t_map	*map;

	void	*img;
	char	*img_addr;
	int		bpp;
	int		ll; //line length
	int		end; //endian

	t_gamer	gamer;
	t_txts	txts;
}			t_mcraft;

/* ========== FUNCTIONS ========== */

/* ----- Initttt ----- */
void	cub_init(t_mcraft *mcraft);
void	init_win(t_mcraft *mcraft, int w, int h);
void	win_bk(t_mcraft *mcraft);

/* ----- Event Hanling ----- */
void	keyhooks(t_mcraft *mcraft);
int		keys(int keycode, t_mcraft *mcraft);
int		mouse(int click, int x, int y);
int		exit_win(t_mcraft *mcraft);

/* ----- Rendering ----- */
void	draw_pixel(t_mcraft *mcraft, int x, int y, int color);
int		colors(char *str);

/* ----- Map Parsing ----- */
int		parse_map(t_mcraft *mcraft, char *file);
void	cleanup_map(t_map *map);
bool	is_map_valid(t_map *map);
bool	is_enclosed(char **grid);
bool	symbols_valid(t_map *map);

void	cleanup_game(t_mcraft *mcraft);
void	free_array(char **array);
int		get_longest_row(char **grid, char *key);
t_map	*create_map(char *file, t_mcraft *mcraft);
int		get_longest_row(char **grid, char *key);
void	exit_err(char *str);

int		maximize(t_mcraft *mcraft);
int		minimize(t_mcraft *mcraft);

/*------- game ---------*/

void	draw_square(int x, int y, int size, int color, t_mcraft *mcraft);
int		key_release(int keycode, t_gamer *gamer);
int		key_press(int keycode, t_gamer *gamer);
void	init_player(t_gamer *gamer);

/* ------ maps --------- */

char	**m1(void);
char	**m2(void);
char	**m3(void);

//Margos
// t_mcraft	*create_game(char *file_path);
// int open_file(char *path);
// int get_longest_row(char **grid, char *key);
// char	**read_map(int fd, t_map *map);
// int close(int fd);
// bool	is_enclosed(char **grid, int line_count);
// bool	symbols_valid(t_map *map);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:16:58 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/03 01:46:10 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ========== INCLUDES ========== */
# include "../libs/libft/include/libft.h"
# include "../libs/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
# define BLACK 0x000000

# define TX_W 64
# define TX_H 64
# define WIN_W 800 // 1920
# define WIN_H 600 // 1080

# define PI 3.14159265359
# define BLOCK 64

# define P_SPEED 5    // playerspeed
# define R_SPEED 0.05 // rot speed

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
	int		row_index;
}			t_map;

enum		ID
{
	NO,
	SO,
	WE,
	EA,
	FL,
	CE
};
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

	char	*floor_id;
	char	*ceiling_id;

	int		floor_color;
	int		ceiling_color;
}			t_txts;

typedef struct s_gamer
{
	float	x;
	float	y;
	float	angle;

	bool k_up; // key_up
	bool	k_down;
	bool	k_left;
	bool	k_right;

	bool	rot_l;
	bool	rot_r;
}			t_gamer;

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
	int ll;  // line length
	int end; // endian

	t_gamer	gamer;
	t_txts	txts;
}			t_mcraft;

/* ========== FUNCTIONS ========== */

/* ----- Initttt ----- */
void		cub_init(t_mcraft *mcraft);
void		init_win(t_mcraft *mcraft, int w, int h);
void		win_bk(t_mcraft *mcraft);

/* ----- Event Hanling ----- */
void		keyhooks(t_mcraft *mcraft);
int			keys(int keycode, t_mcraft *mcraft);
int			mouse(t_mcraft *mcraft, int click, int x, int y);
int			exit_win(t_mcraft *mcraft);

/* ----- Rendering ----- */
void		draw_pixel(t_mcraft *mcraft, int x, int y, int color);
int			colors(char *str);
int			render_img(t_mcraft *mcraft);

/* ----- Map Parsing ----- */
int			parse(t_mcraft *mcraft, char *file);
int			parse_elements(t_mcraft *mcraft, int fd);
void		cleanup_map(t_map *map);
bool		colour_valid(char *line, int bitmask);
bool		texture_valid(char *path, int bitmask);
bool		is_map_valid(t_map *map);
bool		is_enclosed(t_map *map);
bool		symbols_valid(t_map *map);
int			parse_textures_and_colors(t_mcraft *mcraft, char *line);

void		cleanup_game(t_mcraft *mcraft);
void		free_array(char **array);
int			get_longest_row(t_map *map, char *key);
t_map		*create_map(int fd, char *line, t_mcraft *mcraft);
// int		get_longest_row(char **grid, char *key);
void		exit_err(char *str);

int			maximize(t_mcraft *mcraft);
int			minimize(t_mcraft *mcraft);

/*------- player ---------*/

void		draw_crosshairs(t_mcraft *mcraft, int color);
int			key_release(int keycode, t_mcraft *mcraft);
void		init_player(t_gamer *gamer);
void		move_player(t_mcraft *mcraft);

/* ------ utils ------- */
t_mcraft	*get_mcraft(t_mcraft *mcraft);

// Margos
// t_mcraft	*create_game(char *file_path);
// int open_file(char *path);
// int get_longest_row(char **grid, char *key);
// char	**read_map(int fd, t_map *map);
// int close(int fd);
// bool	is_enclosed(char **grid, int line_count);
// bool	symbols_valid(t_map *map);

#endif
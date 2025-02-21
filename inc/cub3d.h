/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:16:58 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/21 17:54:22 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ========== INCLUDES ========== */
# include "../libs/libft/include/libft.h"
# include "../libs/mlx/mlx.h"
# include "colors.h"
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

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define EMPTY '0'
# define WALL '1'
# define START 'N'

# define TX_W 64
# define TX_H 64
# define WIN_W 800 // 1920
# define WIN_H 600 // 1080

# define PI 3.14159265359
# define BLOCK 64

# define P_SPEED 5    // playerspeed
# define R_SPEED 0.05 // rot speed

# define MINI_H
# define MINI_W
# define TILE_S 10

# define OFF_X 10 // offsets for where the minimap is drawn
# define OFF_Y 10

# define STEP_SIZE 1.0

# define FOV 60.0
# define PLANE_DIST tan((FOV / 2.0) * (PI / 180.0))

/* ========== STRUCTS ========== */
typedef struct s_mcraft	t_mcraft;

typedef struct s_pos
{
	int					x;
	int					y;
}						t_pos;
typedef struct s_vector
{
	int x;     // x coord of vector relative to screen
	int y;     // current pixel index of vector
	float y0;    // y start index of drawing texture
	float y1;    // y end index of drawing texture
	float h;     // ray height
	int tex_x; // x coord of texture to draw
	int tex_y; // y coord of texture to draw
}						t_vector;

typedef struct s_ray
{
	double				curr_x;
	double				curr_y;
	double				ray_dir_x;
	double				ray_dir_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				side_dist_x;
	double				side_dist_y;
	double				perp_wall_dist;
	int					side;
	int					direction;
	int					map_x;
	int					map_y;
	int					draw_start;
	int					draw_end;
	double				wall_x;
	t_pos				step;
}						t_ray;
typedef struct s_map
{
	int					player_start_row;
	int					player_start_col;
	char				**grid;
	int					rows;
	int					cols;
	int					row_index;
	t_mcraft			*mcraft;
}						t_map;

enum					ID
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
	char				*tx_n;
	char				*tx_s;
	char				*tx_e;
	char				*tx_w;

	char				*tx_n_data;
	char				*tx_s_data;
	char				*tx_e_data;
	char				*tx_w_data;

	void				*tx_n_img;
	void				*tx_s_img;
	void				*tx_e_img;
	void				*tx_w_img;

	int					tx_width;
	int					tx_height;

	int					ll;
	int					bpp;
	int					end;

	char				*floor_id;
	char				*ceiling_id;

	int					floor_color;
	int					ceiling_color;
}						t_txts;

typedef struct s_gamer
{
	float				x;
	float				y;
	float				angle;
	int					direction;

	bool				k_up;
	bool				k_down;
	bool				k_left;
	bool				k_right;

	bool				rot_l;
	bool				rot_r;
	double				dir_x;
	double				dir_y;
}						t_gamer;

typedef struct s_mcraft
{
	void				*mlx;
	void				*win;
	int					w;
	int					h;
	char				*file_path;
	t_map				*map;

	void				*img;
	char				*img_addr;
	int					bpp;
	int ll;  // line length
	int end; // endian

	double				camera_h;
	double				camera_x;
	double				plane_x;
	double				plane_y;
	bool				has_changed;
	t_gamer				*gamer;
	t_txts				*txts;
}						t_mcraft;

/* ========== FUNCTIONS ========== */

/* ----- Initttt ----- */
void					cub_init(t_mcraft *mcraft, char **av);
void					init_win(t_mcraft *mcraft, char **av);
void					win_bk(t_mcraft *mcraft);
t_map					*create_map(int fd, char *line, t_mcraft *mcraft);
void					init_window(t_mcraft *mcraft, int w, int h);

/* ----- Event Hanling ----- */
void					keyhooks(t_mcraft *mcraft);
int						keys(int keycode, t_mcraft *mcraft);
int						mouse(t_mcraft *mcraft, int click, int x, int y);
int						exit_win(t_mcraft *mcraft);
int						maximize(t_mcraft *mcraft);
int						minimize(t_mcraft *mcraft);
int						wads_keys(int keycode, t_gamer *gamer);
int						arrow_keys(int keycode, t_gamer *gamer);

/* ----- Rendering ----- */
void					draw_pixel(t_mcraft *mcraft, int x, int y, int color);
int						colors(char *str);
int						render_img(t_mcraft *mcraft);

/* ------- DDA ------- */
int						dda(t_mcraft *mcraft);
t_ray					*init_ray(t_mcraft *mcraft, int x);
void					setup_ray(t_mcraft *mcraft, t_ray *ray, t_pos map_pos);
void					setup_vector(t_mcraft *mcraft, t_ray *ray,
							t_vector *vector, int x);
void					calculate_step_and_sideDist(t_gamer *gamer, t_ray *ray,
							t_pos *map_pos, t_pos *step);
bool					**init_visited(t_map *map);
bool					is_cell_valid(t_map *map, int row, int col);
char					*get_tx_index(int direction);
int						get_texture_color(t_mcraft *mcraft, t_txts *txts,
							int tex_x, int tex_y);
t_pos					set_direction_vector(t_gamer *gamer);
void					draw_vector(t_mcraft *mcraft, t_ray *ray, t_pos map_pos,
							int x);
void					pixel_on_img(t_mcraft *mcraft, int rgb, int x, int y);
void					texture_on_img(t_mcraft *mcraft, t_vector vector,
							char *tx_data);

/* ----- Map Parsing ----- */
int						parse(t_mcraft *mcraft, char *file);
int						parse_elements(t_mcraft *mcraft, int fd);
void					cleanup_map(t_map *map);
void					set_player_direction(int *direction, float *angle,
							char key);
bool					colour_valid(char *line, int bitmask);
bool					texture_valid(char *path, int bitmask);
bool					is_map_valid(t_mcraft *mcraft, t_map *map);
bool					file_valid(char *line, int fd, bool map_read);
bool					is_enclosed(t_map *map);
bool					symbols_valid(t_mcraft *mcraft, t_map *map);
int						parse_textures_and_colors(t_mcraft *mcraft, char *line);
int						create_textures(t_mcraft *mcraft, t_txts *txts);

/* ------ garbage collector ------ */
void					cleanup_game(t_mcraft *mcraft);
void					free_array(char **array);
void					exit_err(char *str);

/*------- player ---------*/
void					draw_crosshairs(t_mcraft *mcraft, int color);
int						key_release(int keycode, t_mcraft *mcraft);
void					init_player(t_gamer **gamer);

/* ------- movement -------- */
void					move_player(t_mcraft *mcraft);
void					move_up(t_mcraft *mcraft, t_gamer *gamer, float cos_a,
							float sin_a);
void					move_down(t_mcraft *mcraft, t_gamer *gamer, float cos_a,
							float sin_a);
void					move_left(t_mcraft *mcraft, t_gamer *gamer, float cos_a,
							float sin_a);
void					move_right(t_mcraft *mcraft, t_gamer *gamer,
							float cos_a, float sin_a);
void					move_arrows(t_mcraft *mcraft, t_gamer *gamer,
							float cos_a, float sin_a);

/* ------ minimap ------ */
void					draw_tile(t_mcraft *mcraft, int start_x, int start_y,
							int tile_size, int color);
void					minimap(t_mcraft *mcraft);
bool					is_wall(t_mcraft *mcraft, float px, float py);
void	player_position(t_mcraft *mcraft); // temp tester function
void					set_player_starting_pos(t_mcraft *mcraft);
void					draw_ray_minimap(t_mcraft *mcraft, float angle);

/* ------ raycasting babyyy ------ */
t_vector				mr_ray(t_mcraft *mcraft, float angle);
void					cast_rays(t_mcraft *mcraft);
float					distance(float x, float y);

/* ------ utils ------- */
t_mcraft				*get_mcraft(t_mcraft *mcraft);
char					*get_tx_data(char *key, t_txts *txts);
int						get_longest_row(t_map *map, char *key);

#endif
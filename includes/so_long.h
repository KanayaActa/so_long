/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <mlx.h>
# include <errno.h>
# include <limits.h>
# include <stdint.h>
# include <string.h>
# include "libft.h"

# define WIDTH 1000
# define HEIGHT 800
# define TILE_SIZE 64

# define HELP_MESSAGE "Usage: ./so_long [MAP.ber]\n \
\n \
Controls:\n \
  General:\n \
    ESC       - Exit the program\n \
\n \
  Player Movement:\n \
    W         - Move up\n \
    S         - Move down\n \
    A         - Move left\n \
    D         - Move right\n"

# define INIT_MLX_ERROR_MESSAGE "Error: Failed to initialize MiniLibX\n"
# define INVALID_MAP_ERROR "Error: Invalid map format\n"
# define INVALID_PATH_ERROR "Error: No valid path in map\n"
# define INVALID_CHAR_ERROR "Error: Invalid character in map\n"
# define MISSING_ELEMENT_ERROR "Error: Missing required element in map\n"
# define DUPLICATE_ELEMENT_ERROR "Error: Duplicate element in map\n"
# define NOT_RECTANGULAR_ERROR "Error: Map is not rectangular\n"
# define NOT_SURROUNDED_ERROR "Error: Map is not surrounded by walls\n"

# define KEY_ESCAPE 65307
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_Q      113
# define KEY_E      101
# define KEY_P      112
# define KEY_UP     65362
# define KEY_DOWN   65364
# define KEY_LEFT   65361
# define KEY_RIGHT  65363
# define KEY_PLUS   61
# define KEY_MINUS  45
# define KEY_SPACE  32

# define PROJECTION_ISOMETRIC 0
# define PROJECTION_PERSPECTIVE 1

# define CAMERA_ROTATION_ANGLE 5
# define CAMERA_ZOOM_STEP 1
# define CAMERA_POSITION_STEP 1.0

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define ENEMY 'X'

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_vector4
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vector4;

typedef struct s_matrix4x4
{
	double	m[4][4];
}	t_matrix4x4;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_camera
{
	t_vector3	position;
	double		zoom;
	double		x_angle;
	double		y_angle;
	double		z_angle;
	int			x_offset;
	int			y_offset;
	t_vector3	target;
	t_vector3	up;
	double		fov;
	double		aspect_ratio;
	double		near;
	double		far;
}	t_camera;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	int		collectibles;
	int		total_collectibles;
	int		has_exit;
	t_vector3	position_3d;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exit;
	int		player;
	t_point	exit_pos;
	t_point	player_pos;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_line_vars
{
	int		dx;
	int		dy;
	int		steps;
	double	x_increment;
	double	y_increment;
	double	x;
	double	y;
	int		i;
	double	t;
	int		color;
}	t_line_vars;

typedef struct s_textures
{
	t_img	wall;
	t_img	empty;
	t_img	collectible;
	t_img	exit;
	t_img	player;
	t_img	enemy;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_textures	textures;
	int			game_over;
	
	// 3D関連
	t_camera	camera;
	t_matrix4x4	projection;
	t_matrix4x4	view;
	int			projection_mode;
	double		**height_map;
}	t_game;

/* Main functions */
void	is_valid_args(int argc, char **argv);
void	option_help(int fd, const char *op);
void	initialize_mlx(t_game *game);
void	init_game(t_game *game);

/* Map functions */
void	init_map(const char *filename, t_map *map);
int		open_file(const char *filename);
t_list	*read_map(int fd);
void	parse_map(t_list *lines, t_map *map);
int		validate_map(t_map *map);
int		check_path(t_map *map);
void	flood_fill(char **map, int x, int y, int *collectibles);

/* Player functions */
void	init_player(t_game *game);
int		move_player(t_game *game, int new_x, int new_y);
void	update_player_position(t_game *game, int new_x, int new_y);

/* Texture functions */
void	load_textures(t_game *game);
void	free_textures(t_game *game);

/* Drawing functions */
void	draw_game(t_game *game);
void	draw_map(t_game *game);
void	draw_player(t_game *game);
void	draw_tile(t_game *game, t_img *img, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* Event functions */
void	setup_hooks(t_game *game);
int		key_press(int keycode, void *param);
int		close_window(void *param);

/* 3D functions */
void	init_3d(t_game *game);
void	init_camera(t_game *game);
void	reset_camera(t_game *game);
void	convert_2d_to_3d_map(t_game *game);
void	draw_3d_map(t_game *game);
void	draw_3d_player(t_game *game);
void	draw_3d_collectibles(t_game *game);
void	draw_3d_exit(t_game *game);
void	draw_3d_enemies(t_game *game);
void	draw_3d_game(t_game *game);
void	setup_hooks_3d(t_game *game);
t_point	project(t_vector3 v, t_game *game);
t_point	isometric_projection(t_vector3 v, t_game *game);
t_point	perspective_projection(t_vector3 v, t_game *game);
t_vector3	rotate(t_vector3 v, t_camera *cam);
void	draw_line(t_game *game, t_point p0, t_point p1, int color);
void	draw_circle(t_game *game, t_point center, int radius, int color);

/* Matrix and Vector functions */
t_matrix4x4	matrix_multiply(t_matrix4x4 m1, t_matrix4x4 m2);
t_vector4	matrix_vector_multiply(t_matrix4x4 m, t_vector4 v);
t_vector4	vector3_to_vector4(t_vector3 v);
void	matrix4x4_zero(t_matrix4x4 *m);
t_vector3	vector_normalize(t_vector3 v);
t_vector3	vector_subtract(t_vector3 v1, t_vector3 v2);
t_vector3	vector_cross(t_vector3 v1, t_vector3 v2);
double	vector_dot(t_vector3 v1, t_vector3 v2);
t_matrix4x4	look_at(t_vector3 eye, t_vector3 target, t_vector3 up);
t_matrix4x4	perspective(double fov, double aspect, double near, double far);

/* Utility functions */
void	check_alloc_error(void *ptr);
void	free_map(t_map *map);
void	free_game(t_game *game);
void	error_exit(char *message);

#endif

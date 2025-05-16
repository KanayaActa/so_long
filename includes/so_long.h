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

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define ENEMY 'X'

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	int		collectibles;
	int		total_collectibles;
	int		has_exit;
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

/* Utility functions */
void	check_alloc_error(void *ptr);
void	free_map(t_map *map);
void	free_game(t_game *game);
void	error_exit(char *message);

#endif

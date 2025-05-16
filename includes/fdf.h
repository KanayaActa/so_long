/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:57:15 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/20 12:04:04 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <mlx.h>
# include <errno.h>
# include <limits.h>
# include <stdint.h>
# include "libft.h"

# define WIDTH 1000
# define HEIGHT 800

# define HELP_MESSAGE "Usage: ./fdf [FILE]\n \
\n \
Controls:\n \
  General:\n \
    ESC       - Exit the program\n \
    P         - Toggle projection mode (Isometric/Perspective)\n \
    SPACE     - Reset camera to default position\n \
\n \
  Camera Translation:\n \
    W         - Move up\n \
    S         - Move down\n \
    A         - Move left\n \
    D         - Move right\n \
\n \
  Camera Rotation:\n \
    Q         - Rotate counterclockwise around Z-axis\n \
    E         - Rotate clockwise around Z-axis\n \
    Arrow Up  - Rotate upward around X-axis\n \
    Arrow Down- Rotate downward around X-axis\n \
    Arrow Left- Rotate left around Y-axis\n \
    Arrow Right- Rotate right around Y-axis\n \
\n \
  Zoom:\n \
    +         - Zoom in\n \
    -         - Zoom out\n"

# define INIT_MLX_ERROR_MESSAGE "Error: Failed to initialize MiniLibX\n"
# define RANGE_ERROR_MESSAGE "Error: Number out of range\n"
# define INT_RANGE_ERROR_MESSAGE "Error: Value out of int range\n"
# define INVALID_CHAR_ERROR_MESSAGE "Error: Invalid characters\n"

# define CAMERA_OFFSET 10
# define CAMERA_ROTATION_ANGLE 5
# define CAMERA_ZOOM_STEP 1
# define CAMERA_POSITION_STEP 1.0

# define PROJECTION_ISOMETRIC 0
# define PROJECTION_PERSPECTIVE 1

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

typedef struct s_map
{
	int	width;
	int	height;
	int	**z_values;
	int	**color;
}	t_map;

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

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	t_map		map;
	t_camera	camera;
	t_matrix4x4	projection;
	t_matrix4x4	view;
	int			projection_mode;
}	t_data;

typedef struct s_fill_ctx
{
	char	**split;
	char	*endptr;
	long	num;
	int		i;
	int		j;
}	t_fill_ctx;

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

typedef struct s_draw_vars
{
	int			i;
	int			j;
	t_point		p0;
	t_point		p1;
	t_vector3	v0;
	t_vector3	v1;
}	t_draw_vars;

void		is_valid_args(int argc);
void		option_help(int fd, const char *op);
void		initialize_mlx(t_data *data);
void		init_map(const char *filename, t_map *map);
int			open_file(const char *filename);
t_list		*read_map(int fd);
void		fill_map(t_list *lines, t_map *map);
void		check_alloc_error(void *ptr);
void		set_z_value(int *z_value, t_fill_ctx ctx, \
t_list *lines, t_map *map);
void		free_split(char **split);
void		free_map(t_map *map, int height);
void		init_camera(t_data *data);
t_point		project(t_vector3 v, t_data *data);
t_matrix4x4	matrix_multiply(t_matrix4x4 m1, t_matrix4x4 m2);
t_vector4	vector3_to_vector4(t_vector3 v);
t_vector4	matrix_vector_multiply(t_matrix4x4 m, t_vector4 v);
t_matrix4x4	look_at(t_vector3 eye, t_vector3 target, t_vector3 up);
t_matrix4x4	perspective(double fov, double aspect, double near, double far);
t_vector3	rotate(t_vector3 v, t_camera *cam);
void		draw(t_data *data);
void		mlx_hooks(t_data *data);
int			key_press(int keycode, void *param);
int			close_window(void *param);
void		reset_camera(t_data *data);
t_vector3	rotate_camera_direction(t_camera *cam);
void		update_camera(t_data *data);

t_vector3	vector_subtract(t_vector3 a, t_vector3 b);
t_vector3	vector_normalize(t_vector3 v);
t_vector3	vector_cross(t_vector3 a, t_vector3 b);
double		vector_dot(t_vector3 a, t_vector3 b);
void		matrix4x4_zero(t_matrix4x4 *m);

int			get_color(int z);
int			interpolate_color(int color1, int color2, double t);

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

t_vector3	get_vector(int x_index, int y_index, t_data *data);
t_point		get_point(int x_index, int y_index, t_data *data);
void		draw_horizontal_line(t_data *data, int i, int j);
void		draw_vertical_line(t_data *data, int i, int j);
void		draw_line(t_data *data, t_point p0, t_point p1);

void		free_resources(t_data *data);
void		free_for_no_leak(t_fill_ctx *ctx, t_list *lines, t_map *map);

int			calculate_steps(int dx, int dy);

#endif

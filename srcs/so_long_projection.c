/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 05:10:19 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 05:10:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * アイソメトリック投影を行う関数
 */
t_point	isometric_projection(t_vector3 v, t_game *game)
{
	t_point			p;
	const double	angle = 0.523599;
	const double	zoom = game->camera.zoom;

	v.x *= zoom;
	v.y *= zoom;
	v.z *= zoom / 2;
	v = rotate(v, &game->camera);
	p.x = (int)((v.x - v.y) * cos(angle)) + game->camera.x_offset;
	p.y = (int)((v.x + v.y) * sin(angle) - v.z) + game->camera.y_offset;
	p.color = 0xFFFFFF;
	return (p);
}

/**
 * パースペクティブ投影を行う関数
 */
t_point	perspective_projection(t_vector3 v, t_game *game)
{
	t_point		p;
	t_vector4	vec4;
	t_vector4	transformed;
	double		x_ndc;
	double		y_ndc;

	vec4 = vector3_to_vector4(v);
	transformed = matrix_vector_multiply(game->view, vec4);
	transformed = matrix_vector_multiply(game->projection, transformed);
	if (transformed.w != 0)
	{
		transformed.x /= transformed.w;
		transformed.y /= transformed.w;
		transformed.z /= transformed.w;
	}
	x_ndc = (transformed.x + 1.0) / 2.0;
	y_ndc = 1.0 - (transformed.y + 1.0) / 2.0;
	p.x = (int)(x_ndc * WIDTH);
	p.y = (int)(y_ndc * HEIGHT);
	p.color = 0xFFFFFF;
	return (p);
}

/**
 * 投影モードに応じて適切な投影を行う関数
 */
t_point	project(t_vector3 v, t_game *game)
{
	if (game->projection_mode == PROJECTION_ISOMETRIC)
		return (isometric_projection(v, game));
	else
		return (perspective_projection(v, game));
}

/**
 * 3D回転を行う関数
 */
t_vector3	rotate(t_vector3 v, t_camera *cam)
{
	t_vector3	rotated;
	double		x_rad;
	double		y_rad;
	double		z_rad;

	x_rad = cam->x_angle * M_PI / 180.0;
	y_rad = cam->y_angle * M_PI / 180.0;
	z_rad = cam->z_angle * M_PI / 180.0;
	
	// X軸周りの回転
	rotated.y = v.y * cos(x_rad) + v.z * sin(x_rad);
	rotated.z = -v.y * sin(x_rad) + v.z * cos(x_rad);
	rotated.x = v.x;
	v = rotated;
	
	// Y軸周りの回転
	rotated.x = v.x * cos(y_rad) + v.z * sin(y_rad);
	rotated.z = -v.x * sin(y_rad) + v.z * cos(y_rad);
	rotated.y = v.y;
	v = rotated;
	
	// Z軸周りの回転
	rotated.x = v.x * cos(z_rad) - v.y * sin(z_rad);
	rotated.y = v.x * sin(z_rad) + v.y * cos(z_rad);
	rotated.z = v.z;
	
	return (rotated);
}

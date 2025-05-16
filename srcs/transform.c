/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:08:51 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 04:45:45 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix4x4	look_at(t_vector3 eye, t_vector3 target, t_vector3 up)
{
	t_matrix4x4	result;
	t_vector3	zaxis;
	t_vector3	xaxis;
	t_vector3	yaxis;

	zaxis = vector_normalize(vector_subtract(eye, target));
	xaxis = vector_normalize(vector_cross(up, zaxis));
	yaxis = vector_cross(zaxis, xaxis);
	matrix4x4_zero(&result);
	result.m[0][0] = xaxis.x;
	result.m[0][1] = xaxis.y;
	result.m[0][2] = xaxis.z;
	result.m[1][0] = yaxis.x;
	result.m[1][1] = yaxis.y;
	result.m[1][2] = yaxis.z;
	result.m[2][0] = zaxis.x;
	result.m[2][1] = zaxis.y;
	result.m[2][2] = zaxis.z;
	result.m[0][3] = -vector_dot(xaxis, eye);
	result.m[1][3] = -vector_dot(yaxis, eye);
	result.m[2][3] = -vector_dot(zaxis, eye);
	result.m[3][3] = 1.0;
	return (result);
}

t_matrix4x4	perspective(double fov, double aspect, double near, double far)
{
	t_matrix4x4	result;
	double		f;

	matrix4x4_zero(&result);
	f = 1.0 / tan(fov / 2.0);
	result.m[0][0] = f / aspect;
	result.m[1][1] = f;
	result.m[2][2] = (far + near) / (near - far);
	result.m[2][3] = (2 * far * near) / (near - far);
	result.m[3][2] = -1.0;
	return (result);
}

t_vector3	rotate(t_vector3 v, t_camera *cam)
{
	t_vector3	rotated;
	double		x_rad;
	double		y_rad;
	double		z_rad;

	x_rad = cam->x_angle * M_PI / 180.0;
	y_rad = cam->y_angle * M_PI / 180.0;
	z_rad = cam->z_angle * M_PI / 180.0;
	rotated.y = v.y * cos(x_rad) + v.z * sin(x_rad);
	rotated.z = -v.y * sin(x_rad) + v.z * cos(x_rad);
	rotated.x = v.x;
	v = rotated;
	rotated.x = v.x * cos(y_rad) + v.z * sin(y_rad);
	rotated.z = -v.x * sin(y_rad) + v.z * cos(y_rad);
	rotated.y = v.y;
	v = rotated;
	rotated.x = v.x * cos(z_rad) - v.y * sin(z_rad);
	rotated.y = v.x * sin(z_rad) + v.y * cos(z_rad);
	rotated.z = v.z;
	return (rotated);
}

void	reset_camera(t_data *data)
{
	init_camera(data);
	draw(data);
}

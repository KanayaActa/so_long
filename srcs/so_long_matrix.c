/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 05:10:19 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 05:10:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * 行列を0で初期化する関数
 */
void	matrix4x4_zero(t_matrix4x4 *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m->m[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

/**
 * 単位行列を作成する関数
 */
void	matrix4x4_identity(t_matrix4x4 *m)
{
	matrix4x4_zero(m);
	m->m[0][0] = 1.0;
	m->m[1][1] = 1.0;
	m->m[2][2] = 1.0;
	m->m[3][3] = 1.0;
}

/**
 * 行列の積を計算する関数
 */
t_matrix4x4	matrix_multiply(t_matrix4x4 m1, t_matrix4x4 m2)
{
	t_matrix4x4	result;
	int			i;
	int			j;
	int			k;

	matrix4x4_zero(&result);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

/**
 * 行列とベクトルの積を計算する関数
 */
t_vector4	matrix_vector_multiply(t_matrix4x4 m, t_vector4 v)
{
	t_vector4	result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return (result);
}

/**
 * 視点行列を作成する関数
 */
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

/**
 * 透視投影行列を作成する関数
 */
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

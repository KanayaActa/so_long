/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 05:10:19 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 05:10:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * ベクトルの長さを計算する関数
 */
double	vector_length(t_vector3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * ベクトルを正規化する関数
 */
t_vector3	vector_normalize(t_vector3 v)
{
	t_vector3	result;
	double		length;

	length = vector_length(v);
	if (length == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}

/**
 * ベクトルの差を計算する関数
 */
t_vector3	vector_subtract(t_vector3 v1, t_vector3 v2)
{
	t_vector3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

/**
 * ベクトルの和を計算する関数
 */
t_vector3	vector_add(t_vector3 v1, t_vector3 v2)
{
	t_vector3	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

/**
 * ベクトルのスカラー倍を計算する関数
 */
t_vector3	vector_scale(t_vector3 v, double scale)
{
	t_vector3	result;

	result.x = v.x * scale;
	result.y = v.y * scale;
	result.z = v.z * scale;
	return (result);
}

/**
 * ベクトルの外積を計算する関数
 */
t_vector3	vector_cross(t_vector3 v1, t_vector3 v2)
{
	t_vector3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

/**
 * ベクトルの内積を計算する関数
 */
double	vector_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/**
 * 3次元ベクトルを4次元ベクトルに変換する関数
 */
t_vector4	vector3_to_vector4(t_vector3 v)
{
	t_vector4	result;

	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	result.w = 1.0;
	return (result);
}

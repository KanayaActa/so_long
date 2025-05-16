/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 07:45:42 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/28 07:46:16 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector4	vector3_to_vector4(t_vector3 v)
{
	t_vector4	result;

	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	result.w = 1.0;
	return (result);
}

t_vector4	matrix_vector_multiply(t_matrix4x4 m, t_vector4 v)
{
	t_vector4	r;

	r.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	r.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	r.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	r.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return (r);
}

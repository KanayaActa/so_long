/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 07:03:19 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 21:54:50 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	vector_subtract(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	vector_normalize(t_vector3 v)
{
	t_vector3	result;
	const float	len_sq = v.x * v.x + v.y * v.y + v.z * v.z;
	const float	inv_len = 1 / sqrt(len_sq);

	result.x = v.x * inv_len;
	result.y = v.y * inv_len;
	result.z = v.z * inv_len;
	return (result);
}

t_vector3	vector_cross(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	vector_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

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

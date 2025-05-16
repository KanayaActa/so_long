/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:55:53 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/30 00:54:54 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	isometric_projection(t_vector3 v, t_data *data)
{
	t_point			p;
	const double	angle = 0.523599;
	const double	zoom = data->camera.zoom;

	v.x *= zoom;
	v.y *= zoom;
	v.z *= zoom / 2;
	v = rotate(v, &data->camera);
	p.x = (int)((v.x - v.y) * cos(angle)) + data->camera.x_offset;
	p.y = (int)((v.x + v.y) * sin(angle) - v.z) + data->camera.y_offset;
	return (p);
}

t_point	perspective_projection(t_vector3 v, t_data *data)
{
	t_point		p;
	t_vector4	vec4;
	t_vector4	transformed;
	double		x_ndc;
	double		y_ndc;

	vec4 = vector3_to_vector4(v);
	transformed = matrix_vector_multiply(data->view, vec4);
	transformed = matrix_vector_multiply(data->projection, transformed);
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
	return (p);
}

t_point	project(t_vector3 v, t_data *data)
{
	if (data->projection_mode == PROJECTION_ISOMETRIC)
		return (isometric_projection(v, data));
	else
		return (perspective_projection(v, data));
}

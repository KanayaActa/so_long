/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:03:32 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 03:23:54 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_camera(t_data *data)
{
	double	angle;
	double	distance;

	data->projection_mode = 0;
	data->camera.zoom = 20.0;
	data->camera.x_angle = 0.0;
	data->camera.y_angle = 0.0;
	data->camera.z_angle = 0.0;
	data->camera.x_offset = WIDTH / 2;
	data->camera.y_offset = HEIGHT / 2;
	angle = 30.0 * M_PI / 180.0;
	distance = 20.0;
	data->camera.position.x = distance * cos(angle);
	data->camera.position.y = distance * sin(angle);
	data->camera.position.z = distance;
	data->camera.target = (t_vector3){0, 0, 0};
	data->camera.up = (t_vector3){0, 1, 0};
	data->camera.fov = 60.0 * M_PI / 180.0;
	data->camera.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data->camera.near = 0.1;
	data->camera.far = 1000.0;
	data->view = look_at(data->camera.position, data->camera.target, \
									data->camera.up);
	data->projection = perspective(data->camera.fov, data->camera.aspect_ratio, \
									data->camera.near, data->camera.far);
}

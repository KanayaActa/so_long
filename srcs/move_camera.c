/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 07:38:31 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 08:34:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	rotate_camera_direction(t_camera *cam)
{
	t_vector3		direction;
	t_vector3		rotated;
	const double	x_rad = cam->x_angle * M_PI / 180.0;
	const double	y_rad = cam->y_angle * M_PI / 180.0;

	direction.x = 0;
	direction.y = 0;
	direction.z = 1;
	rotated.x = direction.x * cos(y_rad) + direction.z * sin(y_rad);
	rotated.y = direction.y;
	rotated.z = -direction.x * sin(y_rad) + direction.z * cos(y_rad);
	direction = rotated;
	rotated.x = direction.x;
	rotated.y = direction.y * cos(x_rad) - direction.z * sin(x_rad);
	rotated.z = direction.y * sin(x_rad) + direction.z * cos(x_rad);
	return (rotated);
}

void	update_camera(t_data *data)
{
	const t_vector3	direction = rotate_camera_direction(&data->camera);

	data->camera.target.x = data->camera.position.x + direction.x;
	data->camera.target.y = data->camera.position.y + direction.y;
	data->camera.target.z = data->camera.position.z + direction.z;
	data->view = look_at(data->camera.position, data->camera.target, \
	data->camera.up);
}

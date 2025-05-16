/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:07:18 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/30 00:51:20 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_camera_translation(int keycode, t_data *data)
{
	if (data->projection_mode == 0)
	{
		if (keycode == KEY_W)
			data->camera.y_offset -= CAMERA_OFFSET;
		else if (keycode == KEY_S)
			data->camera.y_offset += CAMERA_OFFSET;
		else if (keycode == KEY_A)
			data->camera.x_offset -= CAMERA_OFFSET;
		else if (keycode == KEY_D)
			data->camera.x_offset += CAMERA_OFFSET;
	}
	else
	{
		if (keycode == KEY_W)
			data->camera.position.y += CAMERA_POSITION_STEP;
		else if (keycode == KEY_S)
			data->camera.position.y -= CAMERA_POSITION_STEP;
		else if (keycode == KEY_A)
			data->camera.position.x -= CAMERA_POSITION_STEP;
		else if (keycode == KEY_D)
			data->camera.position.x += CAMERA_POSITION_STEP;
	}
}

static void	handle_camera_rotation(int keycode, t_data *data)
{
	if (keycode == KEY_Q)
		data->camera.z_angle -= CAMERA_ROTATION_ANGLE;
	else if (keycode == KEY_E)
		data->camera.z_angle += CAMERA_ROTATION_ANGLE;
	else if (keycode == KEY_UP)
		data->camera.x_angle -= CAMERA_ROTATION_ANGLE;
	else if (keycode == KEY_DOWN)
		data->camera.x_angle += CAMERA_ROTATION_ANGLE;
	else if (keycode == KEY_LEFT)
		data->camera.y_angle += CAMERA_ROTATION_ANGLE;
	else if (keycode == KEY_RIGHT)
		data->camera.y_angle -= CAMERA_ROTATION_ANGLE;
}

static void	handle_zoom(int keycode, t_data *data)
{
	if (data->projection_mode == PROJECTION_ISOMETRIC)
	{
		if (keycode == KEY_PLUS)
			data->camera.zoom += CAMERA_ZOOM_STEP;
		else if (keycode == KEY_MINUS)
			data->camera.zoom -= CAMERA_ZOOM_STEP;
	}
	else
	{
		if (keycode == KEY_PLUS)
			data->camera.position.z -= CAMERA_POSITION_STEP;
		else if (keycode == KEY_MINUS)
			data->camera.position.z += CAMERA_POSITION_STEP;
	}
}

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_ESCAPE)
		close_window(data);
	else if (keycode == KEY_P)
		data->projection_mode ^= 1;
	else if (keycode == KEY_W || keycode == KEY_A || \
					keycode == KEY_S || keycode == KEY_D)
		handle_camera_translation(keycode, data);
	else if (keycode == KEY_Q || keycode == KEY_E || \
				keycode == KEY_UP || keycode == KEY_DOWN || \
				keycode == KEY_LEFT || keycode == KEY_RIGHT)
		handle_camera_rotation(keycode, data);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		handle_zoom(keycode, data);
	else if (keycode == KEY_SPACE)
		reset_camera(data);
	if (data->projection_mode == PROJECTION_PERSPECTIVE)
		update_camera(data);
	draw(data);
	return (0);
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_resources(data);
	exit(EXIT_SUCCESS);
}

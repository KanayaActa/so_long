/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:39:57 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 05:02:28 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *data, t_point p0, t_point p1)
{
	t_line_vars	vars;

	vars.dx = p1.x - p0.x;
	vars.dy = p1.y - p0.y;
	vars.steps = calculate_steps(vars.dx, vars.dy);
	vars.x_increment = vars.dx / (double)vars.steps;
	vars.y_increment = vars.dy / (double)vars.steps;
	vars.x = p0.x;
	vars.y = p0.y;
	vars.i = 0;
	while (vars.i <= vars.steps)
	{
		vars.t = (double)vars.i / (double)vars.steps;
		vars.color = interpolate_color(p0.color, p1.color, vars.t);
		my_mlx_pixel_put(data, (int)vars.x, (int)vars.y, vars.color);
		vars.x += vars.x_increment;
		vars.y += vars.y_increment;
		vars.i++;
	}
}

void	draw(t_data *data)
{
	int	i;
	int	j;

	mlx_clear_window(data->mlx, data->win);
	ft_bzero(data->addr, WIDTH * HEIGHT * (data->bpp / 8));
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (j < data->map.width - 1)
				draw_horizontal_line(data, i, j);
			if (i < data->map.height - 1)
				draw_vertical_line(data, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

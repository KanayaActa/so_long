/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:29:38 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 04:59:54 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	get_vector(int x_index, int y_index, t_data *data)
{
	t_vector3	v;

	v.x = x_index - data->map.width / 2;
	v.y = y_index - data->map.height / 2;
	v.z = data->map.z_values[y_index][x_index];
	return (v);
}

t_point	get_point(int x_index, int y_index, t_data *data)
{
	const t_vector3	v = get_vector(x_index, y_index, data);
	t_point			p;

	p = project(v, data);
	p.color = data->map.color[y_index][x_index];
	return (p);
}

void	draw_horizontal_line(t_data *data, int i, int j)
{
	const t_point	p0 = get_point(j, i, data);
	const t_point	p1 = get_point(j + 1, i, data);

	draw_line(data, p0, p1);
}

void	draw_vertical_line(t_data *data, int i, int j)
{
	const t_point	p0 = get_point(j, i, data);
	const t_point	p1 = get_point(j, i + 1, data);

	draw_line(data, p0, p1);
}

int	calculate_steps(int dx, int dy)
{
	if (ft_abs(dx) > ft_abs(dy))
		return (ft_abs(dx));
	else
		return (ft_abs(dy));
}

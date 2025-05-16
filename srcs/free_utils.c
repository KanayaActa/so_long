/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 07:43:06 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 04:48:36 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(t_map *map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map->z_values[i]);
		free(map->color[i]);
		i++;
	}
	free(map->z_values);
	free(map->color);
}

void	free_resources(t_data *data)
{
	if (data->map.z_values)
		free_map(&data->map, data->map.height);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	free_for_no_leak(t_fill_ctx *ctx, t_list *lines, t_map *map)
{
	ft_lstclear(&lines, free);
	free_split(ctx->split);
	free_map(map, ctx->i + 1);
}

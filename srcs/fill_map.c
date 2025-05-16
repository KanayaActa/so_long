/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:49:10 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/29 04:52:46 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_fill_map(t_map *map, t_fill_ctx *ctx, t_list *lines)
{
	map->color[ctx->i][ctx->j] = 0;
	ctx->num = ft_strtol(ctx->split[ctx->j], &ctx->endptr, 10);
	set_z_value(&map->z_values[ctx->i][ctx->j], *ctx, lines, map);
	if (!map->color[ctx->i][ctx->j])
		map->color[ctx->i][ctx->j] = get_color(map->z_values[ctx->i][ctx->j]);
	ctx->j++;
}

void	fill_map(t_list *lines, t_map *map)
{
	t_fill_ctx	ctx;
	t_list		*tmp;

	tmp = lines;
	ctx.i = 0;
	while (tmp)
	{
		ctx.split = ft_split(tmp->content, ' ');
		check_alloc_error(ctx.split);
		map->width = 0;
		while (ctx.split[map->width])
			map->width++;
		map->z_values[ctx.i] = (int *)malloc(sizeof(int) * map->width);
		check_alloc_error(map->z_values);
		map->color[ctx.i] = (int *)malloc(sizeof(int) * map->width);
		check_alloc_error(map->color);
		ctx.j = 0;
		while (ctx.j < map->width)
			_fill_map(map, &ctx, lines);
		free_split(ctx.split);
		tmp = tmp->next;
		ctx.i++;
	}
}

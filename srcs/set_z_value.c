/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_z_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 07:19:54 by miwasa            #+#    #+#             */
/*   Updated: 2025/01/30 22:47:26 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_z_value(int *z_value, t_fill_ctx ctx, t_list *lines, t_map *map)
{
	if (errno == ERANGE && (ctx.num == LONG_MAX || ctx.num == LONG_MIN))
	{
		free_for_no_leak(&ctx, lines, map);
		ft_putstr_fd(RANGE_ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (*ctx.endptr == ',')
	{
		ctx.endptr++;
		map->color[ctx.i][ctx.j] = ft_strtol(ctx.endptr, &ctx.endptr, 16);
	}
	if (*ctx.endptr != '\0' && *ctx.endptr != '\n')
	{
		free_for_no_leak(&ctx, lines, map);
		ft_putstr_fd(INVALID_CHAR_ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ctx.num < INT_MIN || ctx.num > INT_MAX)
	{
		free_for_no_leak(&ctx, lines, map);
		ft_putstr_fd(INT_RANGE_ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	*z_value = ctx.num / 2;
}

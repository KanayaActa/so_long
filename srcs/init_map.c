/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:23:25 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/28 05:24:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(const char *filename, t_map *map)
{
	int		fd;
	t_list	*lines;

	fd = open_file(filename);
	lines = read_map(fd);
	map->height = ft_lstsize(lines);
	map->z_values = (int **)malloc(sizeof(int *) * map->height);
	check_alloc_error(map->z_values);
	map->color = (int **)malloc(sizeof(int *) * map->height);
	check_alloc_error(map->color);
	fill_map(lines, map);
	ft_lstclear(&lines, free);
}

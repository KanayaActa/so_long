/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * マップが壁で囲まれているかチェックする関数
 */
static int	is_surrounded_by_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((y == 0 || y == map->height - 1 || 
				x == 0 || x == map->width - 1) && 
				map->grid[y][x] != WALL)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * マップに必要な要素が含まれているかチェックする関数
 */
static int	has_required_elements(t_map *map)
{
	if (map->player != 1)
	{
		if (map->player == 0)
			error_exit(MISSING_ELEMENT_ERROR);
		else
			error_exit(DUPLICATE_ELEMENT_ERROR);
		return (0);
	}
	if (map->exit != 1)
	{
		if (map->exit == 0)
			error_exit(MISSING_ELEMENT_ERROR);
		else
			error_exit(DUPLICATE_ELEMENT_ERROR);
		return (0);
	}
	if (map->collectibles < 1)
	{
		error_exit(MISSING_ELEMENT_ERROR);
		return (0);
	}
	return (1);
}

/**
 * フラッドフィルアルゴリズムで到達可能なマスを探索する関数
 */
void	flood_fill(char **map, int x, int y, int *collectibles)
{
	if (map[y][x] == WALL || map[y][x] == 'V')
		return ;
	if (map[y][x] == COLLECTIBLE)
		(*collectibles)++;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, collectibles);
	flood_fill(map, x - 1, y, collectibles);
	flood_fill(map, x, y + 1, collectibles);
	flood_fill(map, x, y - 1, collectibles);
}

/**
 * マップに有効なパスが存在するかチェックする関数
 */
int	check_path(t_map *map)
{
	char	**temp_map;
	int		i;
	int		collectibles;
	int		can_reach_exit;

	temp_map = (char **)malloc(sizeof(char *) * map->height);
	check_alloc_error(temp_map);
	i = 0;
	while (i < map->height)
	{
		temp_map[i] = ft_strdup(map->grid[i]);
		check_alloc_error(temp_map[i]);
		i++;
	}
	collectibles = 0;
	flood_fill(temp_map, map->player_pos.x, map->player_pos.y, &collectibles);
	can_reach_exit = (temp_map[map->exit_pos.y][map->exit_pos.x] == 'V');
	i = 0;
	while (i < map->height)
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
	return (can_reach_exit && collectibles == map->collectibles);
}

/**
 * マップが有効かどうかを検証する関数
 */
int	validate_map(t_map *map)
{
	if (!is_surrounded_by_walls(map))
	{
		error_exit(NOT_SURROUNDED_ERROR);
		return (0);
	}
	if (!has_required_elements(map))
		return (0);
	if (!check_path(map))
	{
		error_exit(INVALID_PATH_ERROR);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * マップファイルを開く関数
 */
int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * マップファイルを読み込む関数
 */
t_list	*read_map(int fd)
{
	t_list	*lines;
	t_list	*new_node;
	char	*line;

	lines = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		new_node = ft_lstnew(line);
		if (!new_node)
		{
			free(line);
			ft_lstclear(&lines, free);
			check_alloc_error(NULL);
		}
		ft_lstadd_back(&lines, new_node);
	}
	if (!lines)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Empty map file\n", 2);
		exit(EXIT_FAILURE);
	}
	return (lines);
}

/**
 * マップの初期化を行う関数
 */
void	init_map(const char *filename, t_map *map)
{
	int		fd;
	t_list	*lines;

	ft_memset(map, 0, sizeof(t_map));
	fd = open_file(filename);
	lines = read_map(fd);
	close(fd);
	parse_map(lines, map);
	ft_lstclear(&lines, free);
}

/**
 * マップの解放を行う関数
 */
void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

/**
 * マップの文字が有効かチェックする関数
 */
static int	is_valid_char(char c)
{
	return (c == EMPTY || c == WALL || c == COLLECTIBLE || 
			c == EXIT || c == PLAYER || c == ENEMY);
}

/**
 * マップの行を解析する関数
 */
static void	process_map_line(t_map *map, char *line, int y)
{
	int	x;

	x = 0;
	while (line[x] && line[x] != '\n')
	{
		if (!is_valid_char(line[x]))
			error_exit(INVALID_CHAR_ERROR);
		if (line[x] == PLAYER)
		{
			map->player++;
			map->player_pos.x = x;
			map->player_pos.y = y;
		}
		else if (line[x] == EXIT)
		{
			map->exit++;
			map->exit_pos.x = x;
			map->exit_pos.y = y;
		}
		else if (line[x] == COLLECTIBLE)
			map->collectibles++;
		map->grid[y][x] = line[x];
		x++;
	}
	if (x != map->width)
		error_exit(NOT_RECTANGULAR_ERROR);
}

/**
 * マップを解析する関数
 */
void	parse_map(t_list *lines, t_map *map)
{
	t_list	*current;
	int		y;
	int		line_len;

	map->height = ft_lstsize(lines);
	current = lines;
	line_len = ft_strlen((char *)current->content);
	if (line_len > 0 && ((char *)current->content)[line_len - 1] == '\n')
		line_len--;
	map->width = line_len;
	map->grid = (char **)malloc(sizeof(char *) * map->height);
	check_alloc_error(map->grid);
	y = 0;
	while (current)
	{
		map->grid[y] = (char *)malloc(sizeof(char) * (map->width + 1));
		check_alloc_error(map->grid[y]);
		ft_memset(map->grid[y], 0, map->width + 1);
		process_map_line(map, (char *)current->content, y);
		current = current->next;
		y++;
	}
}

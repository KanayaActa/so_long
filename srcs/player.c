/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * プレイヤーの初期化を行う関数
 */
void	init_player(t_game *game)
{
	game->player.x = game->map.player_pos.x;
	game->player.y = game->map.player_pos.y;
	game->player.moves = 0;
	game->player.collectibles = 0;
	game->player.total_collectibles = game->map.collectibles;
	game->player.has_exit = 0;
}

/**
 * プレイヤーの移動を処理する関数
 */
int	move_player(t_game *game, int new_x, int new_y)
{
	char	target_cell;

	if (new_x < 0 || new_x >= game->map.width || 
		new_y < 0 || new_y >= game->map.height)
		return (0);
	target_cell = game->map.grid[new_y][new_x];
	if (target_cell == WALL)
		return (0);
	if (target_cell == ENEMY)
	{
		ft_putstr_fd("Game Over! You touched an enemy.\n", 1);
		game->game_over = 1;
		return (1);
	}
	if (target_cell == COLLECTIBLE)
	{
		game->player.collectibles++;
		game->map.grid[new_y][new_x] = EMPTY;
	}
	if (target_cell == EXIT)
	{
		if (game->player.collectibles == game->player.total_collectibles)
		{
			ft_putstr_fd("Congratulations! You won!\n", 1);
			game->game_over = 1;
		}
		else
		{
			ft_putstr_fd("Collect all items before exiting!\n", 1);
			return (0);
		}
	}
	update_player_position(game, new_x, new_y);
	return (1);
}

/**
 * プレイヤーの位置を更新する関数
 */
void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map.grid[game->player.y][game->player.x] = EMPTY;
	game->player.x = new_x;
	game->player.y = new_y;
	game->map.grid[new_y][new_x] = PLAYER;
	game->player.moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->player.moves, 1);
	ft_putstr_fd("\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * キー入力を処理する関数
 */
int	key_press(int keycode, void *param)
{
	t_game	*game;
	int		moved;

	game = (t_game *)param;
	moved = 0;
	if (keycode == KEY_ESCAPE)
		close_window(param);
	if (game->game_over)
		return (0);
	if (keycode == KEY_W)
		moved = move_player(game, game->player.x, game->player.y - 1);
	else if (keycode == KEY_A)
		moved = move_player(game, game->player.x - 1, game->player.y);
	else if (keycode == KEY_S)
		moved = move_player(game, game->player.x, game->player.y + 1);
	else if (keycode == KEY_D)
		moved = move_player(game, game->player.x + 1, game->player.y);
	if (moved)
		draw_game(game);
	return (0);
}

/**
 * ウィンドウを閉じる関数
 */
int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * フックを設定する関数
 */
void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, close_window, game);
}

/**
 * MLXを初期化する関数
 */
void	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(INIT_MLX_ERROR_MESSAGE, 2);
		free_map(&game->map);
		exit(EXIT_FAILURE);
	}
}

/**
 * 引数の検証を行う関数
 */
void	is_valid_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Usage: ./so_long [MAP.ber]\n", 2);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Map file must have .ber extension\n", 2);
		exit(EXIT_FAILURE);
	}
}

/**
 * ヘルプメッセージを表示する関数
 */
void	option_help(int fd, const char *op)
{
	if (op && ft_strncmp(op, "--help", 7) == 0)
	{
		ft_putstr_fd(HELP_MESSAGE, fd);
		exit(EXIT_SUCCESS);
	}
}

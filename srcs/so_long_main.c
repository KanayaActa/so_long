/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * エラーメッセージを表示して終了する関数
 */
void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

/**
 * ゲームの初期化を行う関数
 */
void	init_game(t_game *game)
{
	game->game_over = 0;
	game->player.moves = 0;
	game->player.collectibles = 0;
	game->player.total_collectibles = game->map.collectibles;
	game->player.has_exit = 0;
	game->player.x = game->map.player_pos.x;
	game->player.y = game->map.player_pos.y;
}

/**
 * ゲームのリソースを解放する関数
 */
void	free_game(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	free_textures(game);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * メイン関数
 */
int	main(int argc, char **argv)
{
	const char	*filename = argv[1];
	t_game		game;

	ft_memset(&game, 0, sizeof(t_game));
	is_valid_args(argc, argv);
	option_help(STDOUT_FILENO, filename);
	init_map(filename, &game.map);
	if (!validate_map(&game.map))
		error_exit(INVALID_MAP_ERROR);
	initialize_mlx(&game);
	game.win = mlx_new_window(game.mlx, 
		game.map.width * TILE_SIZE, 
		game.map.height * TILE_SIZE, 
		"so_long");
	game.img.img = mlx_new_image(game.mlx, 
		game.map.width * TILE_SIZE, 
		game.map.height * TILE_SIZE);
	game.img.addr = mlx_get_data_addr(game.img.img, 
		&game.img.bpp, 
		&game.img.line_length, 
		&game.img.endian);
	init_game(&game);
	load_textures(&game);
	draw_game(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}

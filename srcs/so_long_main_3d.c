/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 05:10:19 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 05:10:19 by miwasa           ###   ########.fr       */
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
	
	// 3D関連の初期化
	init_3d(game);
}

/**
 * ゲームのリソースを解放する関数
 */
void	free_game(t_game *game)
{
	int	i;

	// マップの解放
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
	
	// 高さマップの解放
	if (game->height_map)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->height_map[i])
				free(game->height_map[i]);
			i++;
		}
		free(game->height_map);
	}
	
	// テクスチャの解放
	free_textures(game);
	
	// MLXリソースの解放
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
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "so_long 3D");
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, 
		&game.img.bpp, 
		&game.img.line_length, 
		&game.img.endian);
	init_game(&game);
	load_textures(&game);
	
	// 3Dモードでゲームを描画
	draw_3d_game(&game);
	
	// 3Dモード用のイベントフックを設定
	setup_hooks_3d(&game);
	
	mlx_loop(game.mlx);
	return (0);
}

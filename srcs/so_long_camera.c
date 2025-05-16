/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 05:10:19 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 05:10:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * カメラを初期化する関数
 */
void	init_camera(t_game *game)
{
	// カメラの位置
	game->camera.position.x = 0;
	game->camera.position.y = -game->map.height;
	game->camera.position.z = game->map.height / 2;

	// カメラの回転角度
	game->camera.x_angle = 30;
	game->camera.y_angle = 0;
	game->camera.z_angle = 0;

	// カメラのズーム
	game->camera.zoom = 10.0;

	// カメラのオフセット（画面中央に表示するため）
	game->camera.x_offset = WIDTH / 2;
	game->camera.y_offset = HEIGHT / 2;

	// カメラの注視点
	game->camera.target.x = 0;
	game->camera.target.y = 0;
	game->camera.target.z = 0;

	// カメラの上方向
	game->camera.up.x = 0;
	game->camera.up.y = 0;
	game->camera.up.z = 1;

	// パースペクティブ投影のパラメータ
	game->camera.fov = 60.0 * M_PI / 180.0;
	game->camera.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	game->camera.near = 0.1;
	game->camera.far = 100.0;

	// ビュー行列とプロジェクション行列の更新
	game->view = look_at(game->camera.position, game->camera.target, game->camera.up);
	game->projection = perspective(game->camera.fov, game->camera.aspect_ratio,
		game->camera.near, game->camera.far);
}

/**
 * カメラをリセットする関数
 */
void	reset_camera(t_game *game)
{
	init_camera(game);
	draw_game(game);
}

/**
 * 3D関連の初期化を行う関数
 */
void	init_3d(t_game *game)
{
	// 投影モードの初期化
	game->projection_mode = PROJECTION_ISOMETRIC;

	// カメラの初期化
	init_camera(game);

	// 2Dマップを3D空間に変換
	convert_2d_to_3d_map(game);
}

/**
 * 3D版のゲーム描画関数
 */
void	draw_3d_game(t_game *game)
{
	// ビュー行列とプロジェクション行列の更新
	game->view = look_at(game->camera.position, game->camera.target, game->camera.up);
	game->projection = perspective(game->camera.fov, game->camera.aspect_ratio,
		game->camera.near, game->camera.far);

	// 3Dマップの描画
	draw_3d_map(game);

	// ゲーム要素の描画
	draw_3d_exit(game);
	draw_3d_collectibles(game);
	draw_3d_enemies(game);
	draw_3d_player(game);

	// 画面に表示
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

	// 移動回数を画面に表示
	char moves_str[50];
	sprintf(moves_str, "Moves: %d", game->player.moves);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);

	// コレクティブル数を画面に表示
	char collectibles_str[50];
	sprintf(collectibles_str, "Collectibles: %d/%d", 
		game->player.collectibles, game->player.total_collectibles);
	mlx_string_put(game->mlx, game->win, 10, 40, 0xFFFFFF, collectibles_str);
}

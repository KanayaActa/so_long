/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_events_3d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 05:10:19 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 05:10:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * 3Dモード用のキー入力処理関数
 */
int	key_press_3d(int keycode, void *param)
{
	t_game	*game;
	int		moved;
	int		redraw;

	game = (t_game *)param;
	moved = 0;
	redraw = 0;

	if (keycode == KEY_ESCAPE)
		close_window(param);

	// ゲームプレイ関連のキー
	if (!game->game_over)
	{
		if (keycode == KEY_W)
			moved = move_player(game, game->player.x, game->player.y - 1);
		else if (keycode == KEY_A)
			moved = move_player(game, game->player.x - 1, game->player.y);
		else if (keycode == KEY_S)
			moved = move_player(game, game->player.x, game->player.y + 1);
		else if (keycode == KEY_D)
			moved = move_player(game, game->player.x + 1, game->player.y);
	}

	// カメラ操作関連のキー
	if (keycode == KEY_UP)
	{
		game->camera.x_angle += CAMERA_ROTATION_ANGLE;
		redraw = 1;
	}
	else if (keycode == KEY_DOWN)
	{
		game->camera.x_angle -= CAMERA_ROTATION_ANGLE;
		redraw = 1;
	}
	else if (keycode == KEY_LEFT)
	{
		game->camera.y_angle += CAMERA_ROTATION_ANGLE;
		redraw = 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		game->camera.y_angle -= CAMERA_ROTATION_ANGLE;
		redraw = 1;
	}
	else if (keycode == KEY_Q)
	{
		game->camera.z_angle += CAMERA_ROTATION_ANGLE;
		redraw = 1;
	}
	else if (keycode == KEY_E)
	{
		game->camera.z_angle -= CAMERA_ROTATION_ANGLE;
		redraw = 1;
	}
	else if (keycode == KEY_PLUS)
	{
		game->camera.zoom += CAMERA_ZOOM_STEP;
		redraw = 1;
	}
	else if (keycode == KEY_MINUS)
	{
		game->camera.zoom -= CAMERA_ZOOM_STEP;
		redraw = 1;
	}
	else if (keycode == KEY_SPACE)
	{
		reset_camera(game);
		redraw = 1;
	}
	else if (keycode == KEY_P)
	{
		game->projection_mode = !game->projection_mode;
		redraw = 1;
	}

	// 再描画
	if (moved || redraw)
		draw_3d_game(game);

	return (0);
}

/**
 * 3Dモード用のフックを設定する関数
 */
void	setup_hooks_3d(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press_3d, game);
	mlx_hook(game->win, 17, 0, close_window, game);
}

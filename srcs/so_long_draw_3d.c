/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_draw_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 05:10:19 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 05:10:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * 線を描画する関数
 */
void	draw_line(t_game *game, t_point p0, t_point p1, int color)
{
	t_line_vars	vars;

	vars.dx = abs(p1.x - p0.x);
	vars.dy = abs(p1.y - p0.y);
	vars.steps = vars.dx > vars.dy ? vars.dx : vars.dy;
	if (vars.steps == 0)
		return ;
	vars.x_increment = (double)(p1.x - p0.x) / vars.steps;
	vars.y_increment = (double)(p1.y - p0.y) / vars.steps;
	vars.x = p0.x;
	vars.y = p0.y;
	vars.i = 0;
	vars.color = color;
	while (vars.i <= vars.steps)
	{
		if (vars.x >= 0 && vars.x < WIDTH && vars.y >= 0 && vars.y < HEIGHT)
			my_mlx_pixel_put(&game->img, (int)vars.x, (int)vars.y, vars.color);
		vars.x += vars.x_increment;
		vars.y += vars.y_increment;
		vars.i++;
	}
}

/**
 * 円を描画する関数
 */
void	draw_circle(t_game *game, t_point center, int radius, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = radius;
	d = 3 - 2 * radius;
	while (y >= x)
	{
		my_mlx_pixel_put(&game->img, center.x + x, center.y + y, color);
		my_mlx_pixel_put(&game->img, center.x + y, center.y + x, color);
		my_mlx_pixel_put(&game->img, center.x - x, center.y + y, color);
		my_mlx_pixel_put(&game->img, center.x - y, center.y + x, color);
		my_mlx_pixel_put(&game->img, center.x + x, center.y - y, color);
		my_mlx_pixel_put(&game->img, center.x + y, center.y - x, color);
		my_mlx_pixel_put(&game->img, center.x - x, center.y - y, color);
		my_mlx_pixel_put(&game->img, center.x - y, center.y - x, color);
		if (d < 0)
			d += 4 * x++ + 6;
		else
			d += 4 * (x++ - y--) + 10;
	}
}

/**
 * 塗りつぶされた円を描画する関数
 */
void	draw_filled_circle(t_game *game, t_point center, int radius, int color)
{
	int	x;
	int	y;
	int	r2;

	r2 = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= r2)
				my_mlx_pixel_put(&game->img, center.x + x, center.y + y, color);
			x++;
		}
		y++;
	}
}

/**
 * 2Dマップを3D空間に変換する関数
 */
void	convert_2d_to_3d_map(t_game *game)
{
	int	x;
	int	y;

	// 高さマップの初期化
	game->height_map = (double **)malloc(sizeof(double *) * game->map.height);
	check_alloc_error(game->height_map);
	y = 0;
	while (y < game->map.height)
	{
		game->height_map[y] = (double *)malloc(sizeof(double) * game->map.width);
		check_alloc_error(game->height_map[y]);
		x = 0;
		while (x < game->map.width)
		{
			// 壁は高さを持たせる
			if (game->map.grid[y][x] == WALL)
				game->height_map[y][x] = 1.0;
			else
				game->height_map[y][x] = 0.0;
			x++;
		}
		y++;
	}
}

/**
 * 3Dマップを描画する関数
 */
void	draw_3d_map(t_game *game)
{
	int			x;
	int			y;
	t_vector3	v0;
	t_vector3	v1;
	t_point		p0;
	t_point		p1;

	// 背景をクリア
	ft_memset(game->img.addr, 0, game->img.line_length * HEIGHT);

	for (y = 0; y < game->map.height; y++)
	{
		for (x = 0; x < game->map.width; x++)
		{
			// 現在のセルの3D座標
			v0.x = x - game->map.width / 2.0;
			v0.y = y - game->map.height / 2.0;
			v0.z = game->height_map[y][x];

			// 右のセルがある場合、線を引く
			if (x + 1 < game->map.width)
			{
				v1.x = (x + 1) - game->map.width / 2.0;
				v1.y = y - game->map.height / 2.0;
				v1.z = game->height_map[y][x + 1];

				p0 = project(v0, game);
				p1 = project(v1, game);
				draw_line(game, p0, p1, 0xFFFFFF);
			}

			// 下のセルがある場合、線を引く
			if (y + 1 < game->map.height)
			{
				v1.x = x - game->map.width / 2.0;
				v1.y = (y + 1) - game->map.height / 2.0;
				v1.z = game->height_map[y + 1][x];

				p0 = project(v0, game);
				p1 = project(v1, game);
				draw_line(game, p0, p1, 0xFFFFFF);
			}
		}
	}
}

/**
 * プレイヤーを3D空間に描画する関数
 */
void	draw_3d_player(t_game *game)
{
	t_vector3	player_pos;
	t_point		screen_pos;

	// プレイヤーの3D座標
	player_pos.x = game->player.x - game->map.width / 2.0;
	player_pos.y = game->player.y - game->map.height / 2.0;
	player_pos.z = game->height_map[game->player.y][game->player.x] + 0.5; // 少し浮かせる

	// 3D座標から画面座標に変換
	screen_pos = project(player_pos, game);

	// プレイヤーを描画（円）
	draw_filled_circle(game, screen_pos, 5, 0x0000FF);
}

/**
 * コレクティブルを3D空間に描画する関数
 */
void	draw_3d_collectibles(t_game *game)
{
	int			x;
	int			y;
	t_vector3	collectible_pos;
	t_point		screen_pos;

	for (y = 0; y < game->map.height; y++)
	{
		for (x = 0; x < game->map.width; x++)
		{
			if (game->map.grid[y][x] == COLLECTIBLE)
			{
				// コレクティブルの3D座標
				collectible_pos.x = x - game->map.width / 2.0;
				collectible_pos.y = y - game->map.height / 2.0;
				collectible_pos.z = game->height_map[y][x] + 0.3; // 少し浮かせる

				// 3D座標から画面座標に変換
				screen_pos = project(collectible_pos, game);

				// コレクティブルを描画（円）
				draw_filled_circle(game, screen_pos, 3, 0xFFFF00);
			}
		}
	}
}

/**
 * 出口を3D空間に描画する関数
 */
void	draw_3d_exit(t_game *game)
{
	t_vector3	exit_pos;
	t_point		screen_pos;

	// 出口の3D座標
	exit_pos.x = game->map.exit_pos.x - game->map.width / 2.0;
	exit_pos.y = game->map.exit_pos.y - game->map.height / 2.0;
	exit_pos.z = game->height_map[game->map.exit_pos.y][game->map.exit_pos.x] + 0.2; // 少し浮かせる

	// 3D座標から画面座標に変換
	screen_pos = project(exit_pos, game);

	// 出口を描画（円）
	draw_filled_circle(game, screen_pos, 4, 0x00FF00);
}

/**
 * 敵を3D空間に描画する関数
 */
void	draw_3d_enemies(t_game *game)
{
	int			x;
	int			y;
	t_vector3	enemy_pos;
	t_point		screen_pos;

	for (y = 0; y < game->map.height; y++)
	{
		for (x = 0; x < game->map.width; x++)
		{
			if (game->map.grid[y][x] == ENEMY)
			{
				// 敵の3D座標
				enemy_pos.x = x - game->map.width / 2.0;
				enemy_pos.y = y - game->map.height / 2.0;
				enemy_pos.z = game->height_map[y][x] + 0.4; // 少し浮かせる

				// 3D座標から画面座標に変換
				screen_pos = project(enemy_pos, game);

				// 敵を描画（円）
				draw_filled_circle(game, screen_pos, 4, 0xFF0000);
			}
		}
	}
}

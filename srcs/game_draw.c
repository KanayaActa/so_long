/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * ピクセルを画像に書き込む関数
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * タイルを描画する関数
 */
void	draw_tile(t_game *game, t_img *img, int x, int y)
{
	int	i;
	int	j;
	int	color;
	int	screen_x;
	int	screen_y;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			screen_x = x * TILE_SIZE + i;
			screen_y = y * TILE_SIZE + j;
			if (screen_x >= 0 && screen_x < game->map.width * TILE_SIZE &&
				screen_y >= 0 && screen_y < game->map.height * TILE_SIZE)
			{
				color = *(unsigned int *)(img->addr + ((j * img->height / TILE_SIZE) *
					img->line_length + (i * img->width / TILE_SIZE) * (img->bpp / 8)));
				if ((unsigned int)color != 0xFF000000)  // 透明色でなければ描画
					my_mlx_pixel_put(&game->img, screen_x, screen_y, color);
			}
			j++;
		}
		i++;
	}
}

/**
 * マップを描画する関数
 */
void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == WALL)
				draw_tile(game, &game->textures.wall, x, y);
			else if (game->map.grid[y][x] == EMPTY)
				draw_tile(game, &game->textures.empty, x, y);
			else if (game->map.grid[y][x] == COLLECTIBLE)
				draw_tile(game, &game->textures.collectible, x, y);
			else if (game->map.grid[y][x] == EXIT)
				draw_tile(game, &game->textures.exit, x, y);
			else if (game->map.grid[y][x] == PLAYER)
				draw_tile(game, &game->textures.player, x, y);
			else if (game->map.grid[y][x] == ENEMY)
				draw_tile(game, &game->textures.enemy, x, y);
			x++;
		}
		y++;
	}
}

/**
 * ゲーム全体を描画する関数
 */
void	draw_game(t_game *game)
{
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

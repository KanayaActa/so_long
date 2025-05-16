/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * テクスチャを読み込む関数
 */
static void	load_texture(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Failed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, 
		&img->line_length, &img->endian);
}

/**
 * 全てのテクスチャを読み込む関数
 */
void	load_textures(t_game *game)
{
	load_texture(game, &game->textures.wall, "textures/wall.xpm");
	load_texture(game, &game->textures.empty, "textures/empty.xpm");
	load_texture(game, &game->textures.collectible, "textures/collectible.xpm");
	load_texture(game, &game->textures.exit, "textures/exit.xpm");
	load_texture(game, &game->textures.player, "textures/player.xpm");
	load_texture(game, &game->textures.enemy, "textures/enemy.xpm");
}

/**
 * テクスチャを解放する関数
 */
void	free_textures(t_game *game)
{
	if (game->textures.wall.img)
		mlx_destroy_image(game->mlx, game->textures.wall.img);
	if (game->textures.empty.img)
		mlx_destroy_image(game->mlx, game->textures.empty.img);
	if (game->textures.collectible.img)
		mlx_destroy_image(game->mlx, game->textures.collectible.img);
	if (game->textures.exit.img)
		mlx_destroy_image(game->mlx, game->textures.exit.img);
	if (game->textures.player.img)
		mlx_destroy_image(game->mlx, game->textures.player.img);
	if (game->textures.enemy.img)
		mlx_destroy_image(game->mlx, game->textures.enemy.img);
}

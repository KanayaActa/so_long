/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:56:26 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/28 05:30:25 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	const char	*filename = argv[1];
	t_data		data;

	data.projection_mode = 0;
	is_valid_args(argc);
	option_help(STDOUT_FILENO, filename);
	init_map(filename, &data.map);
	initialize_mlx(&data);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "fdf");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, \
	&data.line_length, &data.endian);
	init_camera(&data);
	draw(&data);
	mlx_hooks(&data);
	mlx_loop(data.mlx);
	return (0);
}

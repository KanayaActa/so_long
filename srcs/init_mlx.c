/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:59:39 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/28 05:59:44 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd(INIT_MLX_ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

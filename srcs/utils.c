/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#             */
/*   Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * メモリ確保エラーをチェックする関数
 */
void	check_alloc_error(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:12:57 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/28 05:12:59 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	is_valid_args(int argc)
{
	if (argc != 2)
	{
		errno = EINVAL;
		perror(NULL);
		option_help(STDERR_FILENO, NULL);
		exit(EXIT_FAILURE);
	}
}

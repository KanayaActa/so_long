/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alloc_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:48:06 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/28 05:48:16 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_alloc_error(void *ptr)
{
	if (!ptr)
	{
		errno = ENOMEM;
		exit((perror(NULL), EXIT_FAILURE));
	}
}

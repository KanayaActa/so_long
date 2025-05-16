/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:14:09 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/28 05:14:28 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	option_help(int fd, const char *op)
{
	if (fd == STDERR_FILENO || !op)
		ft_putstr_fd(HELP_MESSAGE, fd);
	else if (!ft_strcmp(op, "--help") || !ft_strcmp(op, "-h"))
	{
		ft_putstr_fd(HELP_MESSAGE, fd);
		if (fd == STDOUT_FILENO)
			exit(EXIT_SUCCESS);
	}
}

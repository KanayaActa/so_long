/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:46:51 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/30 01:09:30 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*read_map(int fd)
{
	t_list	*lines;
	t_list	*tmp_line;
	char	*line;

	lines = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (0 < errno)
			{
				perror(NULL);
				option_help(STDERR_FILENO, NULL);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		tmp_line = ft_lstnew(line);
		check_alloc_error(line);
		ft_lstadd_back(&lines, tmp_line);
	}
	close(fd);
	return (lines);
}

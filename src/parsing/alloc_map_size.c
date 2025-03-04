/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_map_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:55:51 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/30 19:17:42 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	allocate_map(t_data *data, int size)
{
	if (size == 0)
		return (0);
	data->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map)
		return (0);
	return (1);
}

static int	count_map_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		trim(line);
		if (ft_strrchr("01", line[0]))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

int	alloc_map_size(char *file, t_data *data)
{
	int		fd;
	int		line_count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line_count = count_map_lines(fd);
	close(fd);
	return (allocate_map(data, line_count));
}

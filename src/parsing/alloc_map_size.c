/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_map_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 14:55:51 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-24 14:55:51 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	alloc_map_size(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		trim(line);
		if (ft_strrchr("01", line[0]))
			i++;
		free(line);
	}
	close(fd);
	if (i)
	{
		data->map = malloc(sizeof(char *) * (i + 1));
		if (!data->map)
			return (0);
	}
	else
		return (0);
	return (1);
}

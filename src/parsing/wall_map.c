/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 15:24:00 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-24 15:24:00 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	check_adjacent_spaces(t_data *data, int i, int j)
{
	if (data->map[i][j] == ' ')
		return (1);
	if (data->map[i][j] == '1')
		return (1);
	if (i == 0 || !data->map[i - 1][j] || data->map[i - 1][j] == ' ')
		return (0);
	if (!data->map[i + 1] || !data->map[i + 1][j] || data->map[i + 1][j] == ' ')
		return (0);
	if (j == 0 || data->map[i][j - 1] == ' ')
		return (0);
	if (!data->map[i][j + 1] || data->map[i][j + 1] == ' ')
		return (0);
	return (1);
}

int	wall_map(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	max_len;
	size_t	len;

	max_len = 0;
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!check_adjacent_spaces(data, i, j))
				return (printf("Error: map invalid\n"), 0);
			j++;
		}
		while (j < max_len)
		{
			if (i > 0 && data->map[i - 1][j] && data->map[i - 1][j] != ' '
				&& data->map[i - 1][j] != '1')
				return (printf("Error: map invalid\n"), 0);
			if (data->map[i + 1] && data->map[i + 1][j] && data->map[i
				+ 1][j] != ' ' && data->map[i + 1][j] != '1')
				return (printf("Error: map invalid\n"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

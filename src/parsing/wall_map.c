/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:16:08 by jalbiser          #+#    #+#             */
/*   Updated: 2025/04/14 22:14:36 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	check_adjacent_spaces(t_data *data, int i, int j)
{
	if (data->map[i][j] == ' ' || data->map[i][j] == '1')
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

static int	check_remaining_line(t_data *data, size_t i, size_t j,
		size_t max_len)
{
	while (j < max_len)
	{
		if (i > 0 && j < ft_strlen(data->map[i - 1]) && data->map[i
				- 1][j] != ' ' && data->map[i - 1][j] != '1')
			return (0);
		if (data->map[i + 1] && j < ft_strlen(data->map[i + 1]) && data->map[i
				+ 1][j] != ' ' && data->map[i + 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

static size_t	get_max_len(t_data *data)
{
	size_t	i;
	size_t	len;
	size_t	max_len;

	max_len = 0;
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

int	wall_map(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	max_len;

	max_len = get_max_len(data);
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
		if (!check_remaining_line(data, i, j, max_len))
			return (printf("Error: map invalid\n"), 0);
		i++;
	}
	return (1);
}

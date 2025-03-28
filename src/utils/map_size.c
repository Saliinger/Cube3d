/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:49:59 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 16:19:07 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	map_width(char **map)
{
	int i;
	int j;
	int max_w;
	int vide;

	i = 0;
	max_w = 0;
	while (map[i])
	{
		vide = 0;
		j = 0;
		while (map[i][j] && map[i][j] != '0' && map[i][j] != '1'
			&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != 'S'
			&& map[i][j] != 'N')
			vide++;
		while (map[i][j + vide])
			j++;
		if (j > max_w)
			max_w = j;
		i++;
	}
	return (max_w);
}
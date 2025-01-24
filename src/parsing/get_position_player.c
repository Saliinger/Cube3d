/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 15:16:19 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-24 15:16:19 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void	set_position(t_data *data, int i, int a)
{
	data->player_direction = data->map[i][a];
	data->player_y = i;
	data->player_x = a;
}

int	get_position_player(t_data *data)
{
	int	i;
	int	a;

	i = 0;
	while (data->map[i])
	{
		a = 0;
		while (data->map[i][a])
		{
			if (ft_strchr("NSWE", data->map[i][a]))
			{
				if (!data->player_direction && data->player_x == -1
					&& data->player_y == -1)
					set_position(data, i, a);
				else
					return (printf("Error: duplicate player position\n"), 0);
			}
			a++;
		}
		i++;
	}
	if (!data->player_direction)
		return (printf("Error: problem retrieving player position\n"), 0);
	return (1);
}

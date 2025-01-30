/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:59 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/30 19:14:21 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	valid_map(t_data *data)
{
	int	i;
	int	a;

	i = 0;
	while (data->map[i])
	{
		a = 0;
		while (data->map[i][a])
		{
			if (!ft_strchr(" 01NSWE", data->map[i][a]))
				return (printf("Error: invalid character in map => %c\n",
						data->map[i][a]), 0);
			a++;
		}
		i++;
	}
	return (1);
}

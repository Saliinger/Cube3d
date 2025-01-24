/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 16:25:39 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-23 16:25:39 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

void	free_data(t_data *data)
{
	int	i;

	free(data->no_texture);
	free(data->so_texture);
	free(data->we_texture);
	free(data->ea_texture);
	free(data->floor);
	free(data->ceiling);
	if (data->map)
	{
		i = 0;
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 15:14:46 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-23 15:14:46 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	init_data(t_data *data)
{
	data->player_x = -1;
	data->player_y = -1;
	data->player_direction = '\0';
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	data->map = NULL;
}

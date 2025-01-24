/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 16:39:22 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-23 16:39:22 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	init_keys(t_key *keys, t_data *data)
{
	keys[0] = (t_key){"NO", 2, &data->no_texture, NULL};
	keys[1] = (t_key){"SO", 2, &data->so_texture, NULL};
	keys[2] = (t_key){"WE", 2, &data->we_texture, NULL};
	keys[3] = (t_key){"EA", 2, &data->ea_texture, NULL};
	keys[4] = (t_key){"F", 1, NULL, &data->floor};
	keys[5] = (t_key){"C", 1, NULL, &data->ceiling};
}

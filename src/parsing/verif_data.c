/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 22:40:39 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-23 22:40:39 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	verify_data(t_data *data, int print)
{
	if (!data->no_texture || !data->so_texture || !data->we_texture
		|| !data->ea_texture || !data->floor || !data->ceiling)
	{
		if (print)
			printf("Error: Missing required configuration elements\n");
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:39 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:24:01 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

mlx_texture_t	*get_texture(t_game *game)
{
	if (game->rayon->axis == 1)
	{
		if (game->rayon->x_x > game->player->x)
			return (game->texture->ouest);
		else
			return (game->texture->est);
	}
	else
	{
		if (game->rayon->y_y > game->player->y)
			return (game->texture->nord);
		else
			return (game->texture->sud);
	}
}

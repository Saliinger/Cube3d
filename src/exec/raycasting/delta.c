/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:31:54 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/30 19:49:23 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

// X_AXIS

float	delta_x_x(t_game *game, float delta_y)
{
	float	delta_x;

	delta_x = game->player->x + (delta_y - game->player->y)
		/ tan(game->rayon->angle);
	if (game->rayon->angle > 0 && game->rayon->angle < M_PI)
		delta_x += TILE_SIZE;
	return (delta_x);
}

float	delta_x_y(t_game *game)
{
	float	delta_y;

	delta_y = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
	return (delta_y);
}

// Y_AXIS
float	delta_y_x(t_game *game)
{
	float	delta_x;

	delta_x = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
	return (delta_x);
}

float	delta_y_y(t_game *game, float delta_x)
{
	float	delta_y;

	delta_y = game->player->y + (delta_x - game->player->x)
		* tan(game->rayon->angle);
	if (!(game->rayon->angle > M_PI / 2 && game->rayon->angle < 3 * M_PI / 2))
		delta_y += TILE_SIZE;
	return (delta_y);
}

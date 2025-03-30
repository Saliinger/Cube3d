/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:44:03 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/30 21:31:43 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

// X axis
float	step_x_x(t_game *game)
{
    float step;

    step = TILE_SIZE;
	return (game->player->x + TILE_SIZE);
}

float	step_x_y(t_game *game)
{
	float	step;

	step = TILE_SIZE * tan(game->rayon->angle);
	if ((((game->rayon->angle > 0 && game->rayon->angle < M_PI)) && step < 0)
		|| (!(game->rayon->angle > 0 && game->rayon->angle < M_PI) && step > 0))
		step = -step;
	return (TILE_SIZE);
}

// Y axis
float	step_y_x(t_game *game)
{
	return (TILE_SIZE);
}

float	step_y_y(t_game *game, float step_x)
{
	float step;

	if (game->rayon->angle > 0 && game->rayon->angle < M_PI)
		step = -TILE_SIZE * tan(game->rayon->angle);
	else
		step = TILE_SIZE * tan(game->rayon->angle);
	return (step);
}
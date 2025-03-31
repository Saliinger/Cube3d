/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:44:03 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/31 06:24:43 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

// X_AXIS
float	step_x_x(t_game *game)
{
	float	step;

	step = TILE_SIZE / tan(game->rayon->angle);
	if (game->rayon->angle > M_PI / 2 && game->rayon->angle < 3 * M_PI / 2)
		step = -step;
	return (step);
}

float	step_x_y(t_game *game)
{
	float	step;

	step = TILE_SIZE;
	if (!(game->rayon->angle > 0 && game->rayon->angle < M_PI))
		step = -step;
	return (step);
}

// Y_AXIS
float	step_y_x(t_game *game)
{
	float	step;

	step = TILE_SIZE;
	if (game->rayon->angle > M_PI / 2 && game->rayon->angle < 3 * M_PI / 2)
		step = -step;
	return (step);
}

float	step_y_y(t_game *game)
{
	float step;

	step = TILE_SIZE * tan(game->rayon->angle);
	if (!(game->rayon->angle > 0 && game->rayon->angle < M_PI))
		step = -step;
	return (step);
}
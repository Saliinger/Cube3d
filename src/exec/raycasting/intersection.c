/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:26 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 16:18:39 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

static void	init_delta(t_game *game, float *delta_x, float *delta_y, char flag)
{
	if (flag == 'x')
	{
		*delta_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
		*delta_y = game->player->y + (*delta_x - game->player->x)
			/ tan(game->rayon->angle);
	}
	if (flag == 'y')
	{
		*delta_x = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
		*delta_y = game->player->x + (*delta_x - game->player->y)
			/ tan(game->rayon->angle);
	}
}

float	inter_x(t_game *game, t_rayon *ray)
{
	float	delta_x;
	float	delta_y;
	float	step_x;
	float	step_y;

	init_delta(game, &delta_x, &delta_y, 'x');
	step_x = TILE_SIZE / tan(ray->angle);
	step_y = TILE_SIZE;
	while (wall_hit(game->window->map, delta_x, delta_y))
	{
		delta_x += step_x;
		delta_y += step_y;
	}
	ray->x_x = delta_x;
	ray->x_y = delta_y;
	return (sqrt(pow(delta_x - game->player->x, 2) + pow(delta_y
				- game->player->y, 2)));
}

float	inter_y(t_game *game, t_rayon *ray)
{
	float	delta_x;
	float	delta_y;
	float	step_x;
	float	step_y;

	init_delta(game, &delta_x, &delta_y, 'y');
	step_x = TILE_SIZE;
	step_y = TILE_SIZE / tan(ray->angle);
	while (wall_hit(game->window->map, delta_x, delta_y))
	{
		delta_x += step_x;
		delta_y += step_y;
	}
	ray->y_x = delta_x;
	ray->y_y = delta_y;
	return (sqrt(pow(delta_x - game->player->x, 2) + pow(delta_y
				- game->player->y, 2)));
}

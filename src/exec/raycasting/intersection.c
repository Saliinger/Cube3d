/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:26 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/14 19:22:24 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

float	inter_x(t_game *game, t_rayon *ray)
{
	float	pixel;
	float	delta_x;
	float	delta_y;
	float	step_x;
	float	step_y;

	pixel = 1;
	if (!(ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2))
		pixel = -1;
	delta_x = delta_x_x(game); // bon
	delta_y = delta_x_y(game, delta_x); // bon
	step_x = step_x_x(game);
	step_y = step_x_y(game);
	while (wall_hit(delta_x - pixel, delta_y, game))
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
	float	pixel;
	float	delta_x;
	float	delta_y;
	float	step_x;
	float	step_y;

	pixel = 1;
	if (ray->angle > 0 && ray->angle < M_PI)
		pixel = -1;
	delta_y = delta_y_y(game); // bon
	delta_x = delta_y_x(game, delta_y);
	step_x = step_y_x(game);
	step_y = step_y_y(game);
	while (wall_hit(delta_x, delta_y - pixel, game))
	{
		delta_x += step_x;
		delta_y += step_y;
	}
	ray->y_x = delta_x;
	ray->y_y = delta_y;
	return (sqrt(pow(delta_x - game->player->x, 2) + pow(delta_y
				- game->player->y, 2)));
}

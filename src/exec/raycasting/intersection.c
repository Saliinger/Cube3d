/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:26 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/30 00:51:00 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

// int	inter_check(float angle, float *inter, float *step, int is_horizon)
// {
// 	if (is_horizon)
// 	{
// 		if (angle > 0 && angle < M_PI)
// 		{
// 			*inter += TILE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	else
// 	{
// 		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
// 		{
// 			*inter += TILE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	return (1);
// }

// int	unit_circle(float angle, char c)
// {
// 	if (c == 'x')
// 	{
// 		if (angle > 0 && angle < M_PI)
// 			return (1);
// 	}
// 	else if (c == 'y')
// 	{
// 		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
// 			return (1);
// 	}
// 	return (0);
// }

static void	init_delta(t_game *game, float *delta_x, float *delta_y, char flag)
{
	if (flag == 'x')
	{
		*delta_x = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
		*delta_y = game->player->x + (*delta_y - game->player->y)
			/ tan(game->rayon->angle);
	}
	if (flag == 'y')
	{
		*delta_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
		*delta_y = game->player->y + (*delta_x - game->player->x)
			/ tan(game->rayon->angle);
	}
}

float	inter_x(t_game *game, t_rayon *ray)
{
	float	delta_x;
	float	delta_y;
	float	step_x;
	float	step_y;
	// float	pixel;

	init_delta(game, &delta_x, &delta_y, 'x');
	step_x = TILE_SIZE / tan(ray->angle);
	step_y = TILE_SIZE;
	// pixel = inter_check(game->rayon->angle, &delta_y, &delta_y, 0);
	// if ((unit_circle(ray->angle, 'y') && step_x > 0)
	// 	|| (!unit_circle(ray->angle, 'y') && step_x < 0))
	// 	step_x *= -1;
	while (wall_hit(delta_x, delta_y, game))
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
	// float	pixel;

	init_delta(game, &delta_x, &delta_y, 'y');
	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(ray->angle);
	// pixel = inter_check(game->rayon->angle, &delta_y, &delta_y, 1);
	// if ((unit_circle(ray->angle, 'x') && step_y > 0)
	// 	|| (!unit_circle(ray->angle, 'x') && step_y < 0))
	// 	step_y *= -1;
	while (wall_hit(delta_x, delta_y, game))
	{
		delta_x += step_x;
		delta_y += step_y;
	}
	ray->y_x = delta_x;
	ray->y_y = delta_y;
	return (sqrt(pow(delta_x - game->player->x, 2) + pow(delta_y
				- game->player->y, 2)));
}

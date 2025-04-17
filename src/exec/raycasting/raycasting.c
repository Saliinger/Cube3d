/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:32 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:18:02 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

float	inter_y(t_game *game, float angle)
{
	int		pixel;
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;

	angle = normalize_angle(angle);
	y_step = 32;
	x_step = 32 / tan(angle);
	h_y = floor(game->player->y / 32) * 32;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = game->player->x + (h_y - game->player->y) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y')
			&& x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, game))
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->rayon->x_x = h_x;
	game->rayon->x_y = h_y;
	return (sqrt(pow(h_x - game->player->x, 2) + pow(h_y - game->player->y,
				2)));
}

float	inter_x(t_game *game, float angle)
{
	int		pixel;
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;

	angle = normalize_angle(angle);
	x_step = 32;
	y_step = 32 * tan(angle);
	v_x = floor(game->player->x / 32) * 32;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = game->player->y + (v_x - game->player->x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x')
			&& y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, game))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->rayon->y_x = v_x;
	game->rayon->y_y = v_y;
	return (sqrt(pow(v_x - game->player->x, 2) + pow(v_y - game->player->y,
				2)));
}

void	raycasting(t_game *game)
{
	int		x;
	float	wall_x;
	float	wall_y;

	x = 0;
	wall_x = 0;
	wall_y = 0;
	game->rayon->angle = normalize_angle(game->player->angle - (game->fov_rad
				/ 2));
	while (x < 1920)
	{
		game->rayon->axis = 0;
		wall_y = inter_y(game, game->rayon->angle);
		wall_x = inter_x(game, game->rayon->angle);
		if (wall_x <= wall_y)
			game->rayon->wall_distance = wall_x;
		else
		{
			game->rayon->wall_distance = wall_y;
			game->rayon->axis = 1;
		}
		render(game, x);
		x++;
		game->rayon->angle += game->fov_rad / 1920;
	}
}

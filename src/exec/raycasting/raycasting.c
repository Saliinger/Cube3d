/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:32 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/10 18:08:39 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

float	inter_h(t_game *game)
{
	int		pixel;
	float	angle;
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;

	angle = normalize_angle(game->rayon->angle);
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
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

float	inter_w(t_game *game)
{
	int		pixel;
	float	angle;
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;

	angle = normalize_angle(game->rayon->angle);
	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
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
	while (x < WIN_WIDTH)
	{
		game->rayon->axis = 0;
		wall_y = inter_h(game);
		wall_x = inter_w(game);
		if (wall_x <= wall_y)
			game->rayon->wall_distance = wall_x;
		else
		{
			game->rayon->wall_distance = wall_y;
			game->rayon->axis = 1;
		}
		render(game, x);
		x++;
		game->rayon->angle += game->fov_rad / WIN_WIDTH;
	}
}

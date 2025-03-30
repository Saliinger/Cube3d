/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:32 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/30 00:51:31 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	raycasting(t_game *game)
{
	int x;
	float wall_x;
	float wall_y;

	x = 0;
	wall_x = 0;
	wall_y = 0;
	game->rayon->angle = normalize_angle(game->player->angle - (game->fov_rad
				/ 2));
	while (x < WIN_WIDTH)
	{
		game->rayon->axis = 0;
		wall_x = inter_x(game, game->rayon);
		wall_y = inter_y(game, game->rayon);

		if (wall_x <= wall_y)
			game->rayon->wall_distance = wall_x;
		else
		{
			game->rayon->wall_distance = wall_y;
			game->rayon->axis = Y_AXIS;
		}
		render(game, x);
		// float ray_x = game->player->x + cos(normalize_angle(game->rayon->angle))
		// 	* game->rayon->wall_distance;
		// float ray_y = game->player->y + sin(normalize_angle(game->rayon->angle))
		// 	* game->rayon->wall_distance;
		// draw_line(game, game->player->x, game->player->y, ray_x, ray_y,
		// 	0xFFFFFF);
		x++;
		game->rayon->angle += game->fov_rad / WIN_WIDTH;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:47:49 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:18:02 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cube3d.h"

void	render(t_game *game, int ray)
{
	game->rayon->wall_distance *= cos(game->rayon->angle - game->player->angle);
	game->rayon->wall_height = (32 / game->rayon->wall_distance)
		* ((1920 / 2) / tan(game->fov_rad / 2));
	game->rayon->top_pixel = (1080 / 2) - (game->rayon->wall_height / 2);
	game->rayon->bottom_pixel = (1080 / 2) + (game->rayon->wall_height
			/ 2);
	if (game->rayon->top_pixel < 0)
		game->rayon->top_pixel = 0;
	if (game->rayon->bottom_pixel > 1080)
		game->rayon->bottom_pixel = 1080;
	draw_floor_ceiling(game, ray, game->rayon->top_pixel,
		game->rayon->bottom_pixel);
	draw_wall(game, ray);
}

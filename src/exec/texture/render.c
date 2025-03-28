/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:47:49 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 21:55:31 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cube3d.h"

void	render(t_game *game, int ray)
{
	double	top_pixel;
	double	bottom_pixel;
	double	wall_height;

	game->rayon->wall_distance *= cos(game->rayon->angle - game->player->angle);
	wall_height = (TILE_SIZE / game->rayon->wall_distance) * (WIN_WIDTH / 2)
		/ tan(game->fov_rad / 2);
	top_pixel = (WIN_HEIGHT / 2) - (wall_height / 2);
	bottom_pixel = (WIN_HEIGHT / 2) + (wall_height / 2);
	draw_floor_ceiling(game, ray, top_pixel, bottom_pixel);
	draw_wall(game, ray, top_pixel, bottom_pixel, wall_height);
}

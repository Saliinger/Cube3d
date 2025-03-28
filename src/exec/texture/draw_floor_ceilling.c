/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceilling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:48:50 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 16:18:50 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
{
	int i;
	int floor;
	int ceiling;

	floor = rgb_to_hex(game->data->floor[0], game->data->floor[1],
			game->data->floor[2]);
	ceiling = rgb_to_hex(game->data->ceiling[0], game->data->ceiling[1],
			game->data->ceiling[2]);
	i = b_pix;
	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(game, ray, i++, floor);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, ceiling);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/14 19:12:44 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

static float	init_angle(t_game *game)
{
	float	angle;

	if (game->data->player_direction == 'N')
		angle = 3 * M_PI / 2;
	else if (game->data->player_direction == 'S')
		angle = M_PI / 2;
	else if (game->data->player_direction == 'E')
		angle = 0;
	else if (game->data->player_direction == 'W')
		angle = M_PI;
	else
		angle = 0;
	return (angle);
}

int	init_player(t_game *game)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		ft_exit(game, 1, "Error: player not found");
	player->x = game->data->player_x * (TILE_SIZE / 2);
	player->y = game->data->player_y * (TILE_SIZE / 2);
	player->angle = init_angle(game);
	game->player = player;
	return (0);
}

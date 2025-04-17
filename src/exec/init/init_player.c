/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:18:02 by anoukan          ###   ########.fr       */
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
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		ft_exit(game, 1, "Error: player not found");
	game->player->x = (game->data->player_x * 32) + (32 / 2);
	game->player->y = (game->data->player_y * 32) + (32 / 2);
	game->player->player_speed = 5;
	game->player->angle = init_angle(game);
	return (0);
}

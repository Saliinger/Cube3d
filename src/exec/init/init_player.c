/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/27 20:49:13 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int init_player(t_game *game)
{
  t_player	*player;

  player = malloc(sizeof(t_player));
  if (!player)
    return (1);
  player->x = game->data->player_x;
  player->y = game->data->player_y;
  player->angle = M_PI / 2; // need to add a selector
  game->player = player;
  return (0);
}
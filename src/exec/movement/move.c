/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:19:56 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/31 04:52:25 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	move(void *param)
{
    t_game *game;
    game = (t_game *)param;
    if (mlx_is_key_down(game->window->mlx, MLX_KEY_W))
    {
        game->player->x += cos(game->player->angle) * PLAYER_SPEED;
        game->player->y += sin(game->player->angle) * PLAYER_SPEED;
    }
    if (mlx_is_key_down(game->window->mlx, MLX_KEY_S))
    {
        game->player->x -= cos(game->player->angle) * PLAYER_SPEED;
        game->player->y -= sin(game->player->angle) * PLAYER_SPEED;
    }
    if (mlx_is_key_down(game->window->mlx, MLX_KEY_A))
    {
        game->player->x -= sin(game->player->angle) * PLAYER_SPEED;
        game->player->y += cos(game->player->angle) * PLAYER_SPEED;
    }
    if (mlx_is_key_down(game->window->mlx, MLX_KEY_D))
    {
        game->player->x += sin(game->player->angle) * PLAYER_SPEED;
        game->player->y -= cos(game->player->angle) * PLAYER_SPEED;
    }
    if (mlx_is_key_down(game->window->mlx, MLX_KEY_LEFT))
    {
        game->player->angle -= ROTATION_SPEED;
        if (game->player->angle < 0)
            game->player->angle += 2 * M_PI;
    }
    if (mlx_is_key_down(game->window->mlx, MLX_KEY_RIGHT))
    {
        game->player->angle += ROTATION_SPEED;
        if (game->player->angle > 2 * M_PI)
            game->player->angle -= 2 * M_PI;
    }
}
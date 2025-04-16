/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 06:34:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/16 21:04:04 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

static void	update_player(t_game *game, float next_x, float next_y)
{
	if (!is_wall(next_x, game->player->y, game))
		game->player->x = next_x;
	if (!is_wall(game->player->x, next_y, game))
		game->player->y = next_y;
}

static void	up_down(t_game *game, float *next_x, float *next_y)
{
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_W))
	{
		*next_x = game->player->x + cos(game->player->angle)
			* game->player->player_speed;
		*next_y = game->player->y + sin(game->player->angle)
			* game->player->player_speed;
		update_player(game, *next_x, *next_y);
	}
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_S))
	{
		*next_x = game->player->x - cos(game->player->angle)
			* game->player->player_speed;
		*next_y = game->player->y - sin(game->player->angle)
			* game->player->player_speed;
		update_player(game, *next_x, *next_y);
	}
}

static void	left_right(t_game *game, float *next_x, float *next_y)
{
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_D))
	{
		*next_x = game->player->x - sin(game->player->angle)
			* game->player->player_speed;
		*next_y = game->player->y + cos(game->player->angle)
			* game->player->player_speed;
		update_player(game, *next_x, *next_y);
	}
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_A))
	{
		*next_x = game->player->x + sin(game->player->angle)
			* game->player->player_speed;
		*next_y = game->player->y - cos(game->player->angle)
			* game->player->player_speed;
		update_player(game, *next_x, *next_y);
	}
}

static void	rotate(t_game *game)
{
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_LEFT))
		game->player->angle -= ROTATION_SPEED;
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_RIGHT))
		game->player->angle += ROTATION_SPEED;
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	else if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
}

void	move(void *param)
{
	t_game	*game;
	float	next_x;
	float	next_y;

	game = (t_game *)param;
	up_down(game, &next_x, &next_y);
	left_right(game, &next_x, &next_y);
	rotate(game);
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_ESCAPE))
		ft_exit(game, 0, "Exit game");
}

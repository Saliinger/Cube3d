/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 06:34:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/14 23:19:28 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

static int	is_wall(float x, float y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= game->window->map_width || map_y < 0
		|| map_y >= game->window->map_height)
		return (1);
	return (game->window->map[map_y][map_x] == '1');
}

static void	handler_move(t_game *game, float *next_x, float *next_y)
{
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_A))
	{
		*next_x = game->player->x + sin(game->player->angle) * game->player->player_speed;
		*next_y = game->player->y - cos(game->player->angle) * game->player->player_speed;
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
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_ESCAPE))
		ft_exit(game, 0, "Exit game");
	if (!is_wall(*next_x, game->player->y, game))
		game->player->x = *next_x;
	if (!is_wall(game->player->x, *next_y, game))
		game->player->y = *next_y;
}

void	move(void *param)
{
	t_game	*game;
	float	next_x;
	float	next_y;

	game = (t_game *)param;
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_W))
	{
		next_x = game->player->x + cos(game->player->angle) * game->player->player_speed;
		next_y = game->player->y + sin(game->player->angle) * game->player->player_speed;
	}
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_S))
	{
		next_x = game->player->x - cos(game->player->angle) * game->player->player_speed;
		next_y = game->player->y - sin(game->player->angle) * game->player->player_speed;
	}
	if (mlx_is_key_down(game->window->mlx, MLX_KEY_D))
	{
		next_x = game->player->x - sin(game->player->angle) * game->player->player_speed;
		next_y = game->player->y + cos(game->player->angle) * game->player->player_speed;
	}
	handler_move(game, &next_x, &next_y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:18:22 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:17:50 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	on_cursor_move(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	x_travel;
	double	sens;

	game = param;
	sens = (2.00 / 10000);
	if (!game->cursor)
		return ;
	x_travel = xpos - 1920 / 2;
	game->player->angle += x_travel * sens;
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	else if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	mlx_set_mouse_pos(game->window->mlx, 1920 / 2, 1080 / 2);
	(void)ypos;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
	{
		if (game->cursor)
		{
			game->cursor = 0;
			mlx_set_cursor_mode(game->window->mlx, MLX_MOUSE_NORMAL);
		}
		else
		{
			game->cursor = 1;
			mlx_set_cursor_mode(game->window->mlx, MLX_MOUSE_HIDDEN);
		}
	}
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_REPEAT)
		game->player->player_speed = 20;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_RELEASE)
		game->player->player_speed = 5;
}

void	start_game(t_game *game)
{
	mlx_loop_hook(game->window->mlx, game_loop, game);
	mlx_loop_hook(game->window->mlx, move, game);
	mlx_key_hook(game->window->mlx, &my_keyhook, game);
	mlx_cursor_hook(game->window->mlx, on_cursor_move, game);
	mlx_loop(game->window->mlx);
	ft_exit(game, EXIT_SUCCESS, NULL);
}

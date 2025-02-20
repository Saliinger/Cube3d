/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:16:58 by jalbiser          #+#    #+#             */
/*   Updated: 2025/02/20 22:36:25 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cube3d.h"

void	ft_reles(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->player->move_ad = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->player->move_ad = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->player->move_ws = 0;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->player->move_ws = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player->move_lr = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player->move_lr = 0;
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		exit(0);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->player->move_ad = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->player->move_ad = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game->player->move_ws = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player->move_ws = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player->move_lr = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player->move_lr = 1;
	ft_reles(keydata, game);
}

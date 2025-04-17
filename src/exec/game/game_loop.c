/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:40:21 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:17:50 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_delete_image(game->window->mlx, game->window->fpv);
	game->window->fpv = mlx_new_image(game->window->mlx, 1920, 1080);
	if (!game->window->fpv)
		ft_exit(game, EXIT_FAILURE, "Error: mlx_new_image failed");
	raycasting(game);
	mlx_image_to_window(game->window->mlx, game->window->fpv, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:20 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:17:50 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	init(t_game *game)
{
	int	error;

	error = init_texture(game);
	error += init_window(game);
	error += init_player(game);
	error += init_ray(game);
	mlx_set_mouse_pos(game->window->mlx, 1920 / 2, 1080
		/ 2);
	mlx_set_cursor_mode(game->window->mlx, MLX_MOUSE_HIDDEN);
	game->cursor = 1;
	game->fov_rad = 60 * M_PI / 180;
	if (error > 0)
		ft_exit(game, 1, "Error: init failed");
}

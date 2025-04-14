/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:20 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/14 23:19:54 by jalbiser         ###   ########.fr       */
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
	mlx_set_mouse_pos(game->window->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_set_cursor_mode(game->window->mlx, MLX_MOUSE_HIDDEN);
	game->cursor = 1;
	game->fov_rad = FOV * M_PI / 180;
	if (error > 0)
		ft_exit(game, 1, "Error: init failed");
}

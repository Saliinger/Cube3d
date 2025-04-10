/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:20 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/10 15:13:22 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	init(t_game *game)
{
	int error;

	error = init_texture(game);
	error += init_window(game);
	error += init_player(game);
	error += init_ray(game);
	game->fov_rad = FOV * M_PI / 180;
	if (error > 0)
		ft_exit(game, 1, "Error: init failed");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:20 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 16:18:32 by anoukan          ###   ########.fr       */
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
		exit(1); // add nuke there
}
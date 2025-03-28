/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:18:22 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 16:18:23 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	start_game(t_game *game)
{
	// loop for movement there
	// loop for rendering
	if (DEBUG)
		map_debug(game);
	mlx_loop(game->window->mlx);
}
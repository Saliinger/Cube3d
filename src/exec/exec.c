/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:45 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/31 05:45:45 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

#include "../../include/exec.h"
#include <stdio.h>

void debug_game_data(t_game *game)
{
    if (!game)
    {
        printf("Error: Game structure is NULL.\n");
        return;
    }

    printf("=== Debugging Game Data ===\n");

    // Check if data is properly initialized
    if (!game->data)
        printf("Error: game->data is NULL.\n");
    else
        printf("game->data is initialized.\n");

    // Check window properties
    if (!game->window)
        printf("Error: game->window is NULL.\n");
    else
    {
        printf("game->window->map_width: %d\n", game->window->map_width);
        printf("game->window->map_height: %d\n", game->window->map_height);
    }

    // Check raycasting properties
    if (!game->rayon)
        printf("Error: game->rayon is NULL.\n");
    else
    {
        printf("game->rayon->x_x: %f\n", game->rayon->x_x);
        printf("game->rayon->y_y: %f\n", game->rayon->y_y);
        printf("game->rayon->axis: %d\n", game->rayon->axis);
    }

    // Add checks for other fields in the t_game structure as needed
    printf("===========================\n");
}

int					exec(t_data *data)
{
	t_game	game;

	game.data = data;
	init(&game);
	debug_game_data(&game); // Debugging function call
	start_game(&game);
	return (0);
}

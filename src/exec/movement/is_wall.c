/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:27:54 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:18:02 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	is_wall(float x, float y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / 32);
	map_y = (int)(y / 32);
	if (map_x < 0 || map_x >= game->window->map_width || map_y < 0
		|| map_y >= game->window->map_height)
		return (1);
	return (game->window->map[map_y][map_x] == '1');
}

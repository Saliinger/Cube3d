/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:45 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 01:50:03 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	exec(t_data *data)
{
	t_game	game;

	game.data = data;
	game.player = NULL;
	game.texture = NULL;
	game.window = NULL;
	game.rayon = NULL;
	init(&game);
	start_game(&game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:16 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 01:47:50 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	init_ray(t_game *game)
{
	game->rayon = (t_rayon *)malloc(sizeof(t_rayon));
	if (!game->rayon)
		ft_exit(game, 1, "Error: ray not found");
	return (0);
}

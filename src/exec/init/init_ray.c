/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:16 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/10 15:13:10 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	init_ray(t_game *game)
{
	t_rayon *ray;
	ray = (t_rayon *)malloc(sizeof(t_rayon));
	if (!ray)
		ft_exit(game, 1, "Error: ray not found");
	game->rayon = ray;
	return (0);
}
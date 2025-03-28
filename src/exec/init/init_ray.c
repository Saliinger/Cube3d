/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:16 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 16:18:30 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	init_ray(t_game *game)
{
	t_rayon *ray;
	ray = (t_rayon *)malloc(sizeof(t_rayon));
	if (!ray)
		return (1);
	// add 0 value
	game->rayon = ray;
	return (0);
}
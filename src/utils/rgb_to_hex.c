/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:44:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/10 15:16:33 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

uint32_t	rgb_to_hex(int red, int green, int blue)
{
	uint32_t	hex;

	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
		|| blue > 255)
	{
		fprintf(stderr,
			"Erreur: Les valeurs RGB doivent être entre 0 et 255\n");
		return (0);
	}
	hex = ((uint32_t)red << 24) | ((uint32_t)green << 16) | ((uint32_t)blue << 8) | 0xFF;
	return (hex);
}

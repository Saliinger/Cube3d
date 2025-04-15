/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:44:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/15 18:36:01 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

uint32_t	rgb_to_hex(uint32_t red, uint32_t green, uint32_t blue)
{
	uint32_t	hex;

	hex = (red << 24) | (green << 16) | (blue << 8) | 0xFF;
	return (hex);
}

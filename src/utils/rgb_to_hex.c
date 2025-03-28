/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:44:12 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 21:44:27 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r << 16) | (g << 8) | b);
}
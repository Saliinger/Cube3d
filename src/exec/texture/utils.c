/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:49:26 by anoukan           #+#    #+#             */
/*   Updated: 2025/02/21 14:49:28 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cube3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= WIN_HEIGHT)
		return ;
	mlx_put_pixel(game->fpv, x, y, color);
}

mlx_texture_t	*get_texture(t_game *game, int flag)
{
//	int	angle;
//
//	angle = nor_angle(game->ray->ray_angle);
	if (flag == 0)
	{
    if (game->ray->vert_x > game->player->x) // Ray went right
        return (game->texture->we);
    else
        return (game->texture->ea);
	}
	else
	{
        if (game->ray->horiz_y > game->player->y) // Ray went down, hits north
            return (game->texture->no);
        else // Ray went up, hits south
            return (game->texture->so);
	}
}

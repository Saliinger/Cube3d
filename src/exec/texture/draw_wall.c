/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:03:44 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 02:18:02 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

double	get_x_o(mlx_texture_t *texture, t_game *game)
{
	double	x_o;

	if (game->rayon->axis == 1)
		x_o = (int)fmodf((game->rayon->x_x * (texture->width / 32)),
				texture->width);
	else
		x_o = (int)fmodf((game->rayon->y_y * (texture->width / 32)),
				texture->width);
	return (x_o);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	draw_wall(t_game *game, int ray)
{
	mlx_texture_t	*texture;
	uint32_t		*pixels;
	double			factor;
	double			x_o;
	double			y_o;

	texture = get_texture(game);
	pixels = (uint32_t *)texture->pixels;
	factor = (double)texture->height / game->rayon->wall_height;
	x_o = get_x_o(texture, game);
	y_o = (game->rayon->top_pixel - (1080 / 2) + (game->rayon->wall_height
				/ 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (game->rayon->top_pixel < game->rayon->bottom_pixel)
	{
		mlx_put_pixel(game->window->fpv, ray, game->rayon->top_pixel,
			reverse_bytes(pixels[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		game->rayon->top_pixel++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:03:44 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 22:00:09 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

double	get_x_o(mlx_texture_t *texture, t_game *game)
{
	double	x_o;

	if (game->rayon->axis == 1)
		x_o = (int)fmodf((game->rayon->x_x * (texture->width / TILE_SIZE)),
				texture->width);
	else
		x_o = (int)fmodf((game->rayon->y_y * (texture->width / TILE_SIZE)),
				texture->width);
	return (x_o);
}

void	draw_wall(t_game *game, int ray, double top_pixel, double bottom_pixel, double wall_h)
{
	mlx_texture_t *texture;
	uint32_t *pixels;
	double factor;
	double x_o;
	double y_o;

	texture = get_texture(game);
	pixels = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, game);
	y_o = (top_pixel - (WIN_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (top_pixel < bottom_pixel)
	{
		mlx_put_pixel(game->window->fpv, ray, top_pixel, pixels[(int)y_o * texture->width + (int)x_o]);
		y_o += factor;
		top_pixel++;
	}
}
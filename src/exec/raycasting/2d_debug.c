/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:40:32 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/27 20:40:33 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
 {
 	int	dx;
 	int	dy;
 	int	sx;
 	int	sy;
 	int	err;
 	int	e2;

 	if (x0 < 0 || x0 >= WIN_WIDTH || y0 < 0 || y0 >= WIN_HEIGHT || x1 < 0
 		|| x1 >= WIN_WIDTH || y1 < 0 || y1 >= WIN_HEIGHT)
 		return ;
 	dx = abs(x1 - x0);
 	dy = abs(y1 - y0);
 	sx = x0 < x1 ? 1 : -1;
 	sy = y0 < y1 ? 1 : -1;
 	err = dx - dy;
 	while (1)
 	{
 		mlx_put_pixel(game->window->fpv, x0, y0, color);
 		if (x0 == x1 && y0 == y1)
 			break ;
 		e2 = 2 * err;
 		if (e2 > -dy)
 		{
 			err -= dy;
 			x0 += sx;
 		}
 		if (e2 < dx)
 		{
 			err += dx;
 			y0 += sy;
 		}
 	}
 }

static mlx_image_t *draw_cube(t_game *game, int color)
{
  mlx_image_t *cube = mlx_new_image(game->window->mlx, 64, 64);

  for (int y = 0; y < 64; y++)
    for (int x = 0; x < 64; x++)
      mlx_put_pixel(cube, x, y, color);
  return (cube);
}


void map_debug(t_game *game)
{
	mlx_image_t *wall = draw_cube(game, 6111187);
   	for (int y = 0; game->window->map[y]; y++)
          for (int x = 0; game->window->map[y][x]; x++)
            if (game->window->map[y][x] == 1)
              mlx_image_to_window(game->window->mlx, wall, x * 64, y * 64);
}
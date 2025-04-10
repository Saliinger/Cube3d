/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:40:32 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/10 15:12:03 by anoukan          ###   ########.fr       */
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

mlx_image_t	*make_cube(t_game *game, int color)
{
	mlx_image_t	*cube;

	cube = mlx_new_image(game->window->mlx, TILE_SIZE, TILE_SIZE);
	if (!cube)
		ft_exit(game, EXIT_FAILURE, "Error: mlx_new_image failed");
	for (int i = 0; i < TILE_SIZE; i++)
		for (int j = 0; j < TILE_SIZE; j++)
			mlx_put_pixel(cube, i, j, color);
	return (cube);
}

void	map_debug(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	int gap = 0;
	
	mlx_image_t	*bg = make_cube(game,  rgb_to_hex(120, 120, 120));
	game->window->map_2d = make_cube(game, rgb_to_hex(255, 0, 255));
	while (game->window->map[i])
	{
		j = 0;
		printf("map: %s\n", game->window->map[i]);
		while (game->window->map[i][j])
		{
			if (game->window->map[i][j] == '1')
				mlx_image_to_window(game->window->mlx, game->window->map_2d, j
					* TILE_SIZE, i * TILE_SIZE);
			else
				mlx_image_to_window(game->window->mlx, bg, j * TILE_SIZE,
					i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

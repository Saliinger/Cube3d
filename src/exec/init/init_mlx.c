/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:06 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/16 18:16:43 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	init_texture(t_game *game)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		ft_exit(game, 1, "Error: texture not found");
	texture->nord = mlx_load_png(game->data->no_texture);
	texture->sud = mlx_load_png(game->data->so_texture);
	texture->est = mlx_load_png(game->data->ea_texture);
	texture->ouest = mlx_load_png(game->data->we_texture);
	if (!texture->nord || !texture->sud || !texture->est || !texture->ouest)
		ft_exit(game, 1, "Error: texture not found");
	game->texture = texture;
	return (0);
}

int	init_window(t_game *game)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		ft_exit(game, 1, "Error: window not found");
	window->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D JALBISER / ANOUKAN",
			1);
	if (!window->mlx)
		ft_exit(game, 1, "Error: window not found");
	window->fpv = mlx_new_image(window->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!window->fpv)
		ft_exit(game, 1, "Error: window not found");
	window->map = game->data->map;
	window->map_width = map_width(window->map);
	window->map_height = map_height(window->map);
	game->window = window;
	return (0);
}

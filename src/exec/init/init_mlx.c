/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:49:06 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/17 01:47:37 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	init_texture(t_game *game)
{
	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
		ft_exit(game, 1, "Error: texture not found");
	game->texture->nord = mlx_load_png(game->data->no_texture);
	game->texture->sud = mlx_load_png(game->data->so_texture);
	game->texture->est = mlx_load_png(game->data->ea_texture);
	game->texture->ouest = mlx_load_png(game->data->we_texture);
	if (!game->texture->nord || !game->texture->sud || !game->texture->est
		|| !game->texture->ouest)
		ft_exit(game, 1, "Error: texture not found");
	return (0);
}

int	init_window(t_game *game)
{
	game->window = malloc(sizeof(t_window));
	if (!game->window)
		ft_exit(game, 1, "Error: window not found");
	game->window->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT,
		 "Cub3D JALBISER / ANOUKAN", 1);
	if (!game->window->mlx)
		ft_exit(game, 1, "Error: window not found");
	game->window->fpv = mlx_new_image(game->window->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->window->fpv)
		ft_exit(game, 1, "Error: window not found");
	game->window->map = game->data->map;
	game->window->map_width = map_width(game->window->map);
	game->window->map_height = map_height(game->window->map);
	return (0);
}

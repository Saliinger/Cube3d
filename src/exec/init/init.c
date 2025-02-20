/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:17:27 by jalbiser          #+#    #+#             */
/*   Updated: 2025/02/20 22:48:36 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cube3d.h"

void	init_player(t_game *game)
{
	game->player->x = game->data->player_x * TILE_SIZE + TILE_SIZE / 2;
	game->player->y = game->data->player_y * TILE_SIZE + TILE_SIZE / 2;
	game->player->tile_x = game->data->player_x;
	game->player->tile_y = game->data->player_y;
	if (game->data->player_direction == 'N')
		game->player->direction = (3 * M_PI) / 2;
	else if (game->data->player_direction == 'S')
		game->player->direction = M_PI / 2;
	else if (game->data->player_direction == 'E')
		game->player->direction = 0;
	else if (game->data->player_direction == 'W')
		game->player->direction = M_PI;
	game->player->move_ad = 0;
	game->player->move_lr = 0;
	game->player->move_ws = 0;
}

void	init_texture(t_game *game)
{
	game->texture->ea = mlx_load_png(game->data->ea_texture);
	game->texture->we = mlx_load_png(game->data->we_texture);
	game->texture->so = mlx_load_png(game->data->so_texture);
	game->texture->no = mlx_load_png(game->data->no_texture);
}

// add free to line 51 57

void	init(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return ;
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		return ;
	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
		return ;
	init_texture(game);
	game->ray->fov_rd = (FOV * M_PI) / 180;
	game->map_h = map_height(game->data->map);
	game->map_w = map_width(game->data->map);
	init_player(game);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3D", 0);
}

// debug 2d
// init_map(game); // 2d map
// debug_player(game);
// 2d player  ne need we'll render it virtually from the raycasting

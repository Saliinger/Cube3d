#include "../../include/exec.h"

void loop_hook(void *param)
{
	t_game *game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player->y -= 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player->x -= 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player->y += 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player->x += 1;
	// add rotation
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player->start_angle += 1;
		game->player->end_angle -= 1;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player->start_angle -= 1;
		game->player->end_angle += 1;
	}

	game->player_img->instances->x = game->player->x;
	game->player_img->instances->y = game->player->y;

	raycasting(game);
}

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	t_player player;

    player.x = data->player_x;
    player.y = data->player_y;

    game.player = &player;
	init(&game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}

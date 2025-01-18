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

void player_init(t_game *game)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->x = game->data->player_x;
	player->y = game->data->player_y;
	if (game->data->player_direction == 'N')
	{
		player->start_angle = 315;
		player->end_angle = 45;
	}
	else if (game->data->player_direction == 'S')
	{
		player->start_angle = 135;
		player->end_angle = 225;
	}
	else if (game->data->player_direction == 'E')
	{
		player->start_angle = 45;
		player->end_angle = 135;
	}
	else if (game->data->player_direction == 'W')
	{
		player->start_angle = 225;
		player->end_angle = 315;
	}
	game->player = player;
}

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	player_init(&game);
	init(&game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}

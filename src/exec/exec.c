#include "../../include/cube3d.h"

void loop_hook(void *param)
{
	t_game *game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player_img->instances->y--;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player_img->instances->x--;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player_img->instances->y++;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player_img->instances->x++;
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
	//raycasting(game);
}

void player_init(t_game *game)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->x = game->data->player_x;
	player->y = game->data->player_y;

	// Initialize direction based on input
	if (game->data->player_direction == 'N')
	{
		player->dir_x = 0;  // Facing North
		player->dir_y = -1;
	}
	else if (game->data->player_direction == 'S')
	{
		player->dir_x = 0;  // Facing South
		player->dir_y = 1;
	}
	else if (game->data->player_direction == 'E')
	{
		player->dir_x = 1;  // Facing East
		player->dir_y = 0;
	}
	else if (game->data->player_direction == 'W')
	{
		player->dir_x = -1; // Facing West
		player->dir_y = 0;
	}

	// Initialize the camera plane perpendicular to the direction
	if (game->data->player_direction == 'N' || game->data->player_direction == 'S')
	{
		game->ray->plane_x = 0.66;  // Slight FOV adjustment
		game->ray->plane_y = 0;
	}
	else if (game->data->player_direction == 'E' || game->data->player_direction == 'W')
	{
		game->ray->plane_x = 0;
		game->ray->plane_y = 0.66; // Slight FOV adjustment
	}

	game->player = player;
}

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	game.map_w = 5;
	game.map_h = 5;
	player_init(&game);
	init(&game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_key_hook(game.mlx, ft_hook, &game);
	raycasting(&game);
	mlx_loop(game.mlx);
	return (0);
}

#include "../../../include/cube3d.h"

void	move_player(t_game *game, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(game->player->x + move_x); // get the new x position
	new_y = roundf(game->player->y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (game->data->map[map_grid_y][map_grid_x] != '1' && \
	(game->data->map[map_grid_y][game->player->x / TILE_SIZE] != '1' && \
	game->data->map[game->player->y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		game->player->x = new_x; // move the player
		game->player->y = new_y; // move the player
	}
}

void wasd(t_game *game, mlx_key_data_t key)
{
	double move_x = 0;
	double move_y = 0;

	if (key.key == MLX_KEY_W)
	{
		move_x = sin(game->player->direction) * PLAYER_SPEED;
		move_y = cos(game->player->direction) * PLAYER_SPEED;
	}
	else if (key.key == MLX_KEY_A)
	{
		move_x = -sin(game->player->direction) * PLAYER_SPEED;
		move_y = cos(game->player->direction) * PLAYER_SPEED;
	}
	else if (key.key == MLX_KEY_S)
	{
		move_x = -sin(game->player->direction) * PLAYER_SPEED;
		move_y = -cos(game->player->direction) * PLAYER_SPEED;
	}
	else if (key.key == MLX_KEY_D) {
		move_x = sin(game->player->direction) * PLAYER_SPEED;
		move_y = -cos(game->player->direction) * PLAYER_SPEED;
	}
	move_player(game, move_x, move_y);
}
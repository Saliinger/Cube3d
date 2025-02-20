#include "../../include/cube3d.h"


void rotate_player(t_game *game, int i)
{
	if (i == 1)
	{
		game->player->direction += ROTATION_SPEED; // rotate right
		if (game->player->direction > 2 * M_PI)
			game->player->direction -= 2 * M_PI;
	}
	else
	{
		game->player->direction -= ROTATION_SPEED; // rotate left
		if (game->player->direction < 0)
			game->player->direction += 2 * M_PI;
	}
}

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

void move(t_game *game, float move_x, float move_y)
{
	if (game->player->move_lr == 1) //rotate right
		rotate_player(game, 1);
	if (game->player->move_lr == -1) //rotate left
		rotate_player(game, 0);
	if (game->player->move_ad == 1) //move right
	{
		move_x = -sin(game->player->direction) * PLAYER_SPEED;
		move_y = cos(game->player->direction) * PLAYER_SPEED;
	}
	if (game->player->move_ad == -1) //move left
	{
		move_x = sin(game->player->direction) * PLAYER_SPEED;
		move_y = -cos(game->player->direction) * PLAYER_SPEED;
	}
	if (game->player->move_ws == 1) //move up
	{
		move_x = cos(game->player->direction) * PLAYER_SPEED;
		move_y = sin(game->player->direction) * PLAYER_SPEED;
	}
	if (game->player->move_ws == -1) //move down
	{
		move_x = -cos(game->player->direction) * PLAYER_SPEED;
		move_y = -sin(game->player->direction) * PLAYER_SPEED;
	}
	move_player(game, move_x, move_y); // move the player
}

// loop will be use as a refresh on each move and will render everything
void loop_hook(void *param)
{
	t_game *game = (t_game *)param;
	mlx_delete_image(game->mlx , game->fpv);
	game->fpv = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	// add the hook for the player
	move(game, 0, 0);
	raycasting(game);
	mlx_image_to_window(game->mlx, game->fpv, 0, 0);
}

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	init(&game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_key_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}


#include "../../../include/cube3d.h"

// Main initialization function

// init the struct player
void init_player(t_game *game) {
	game->player->x = game->data->player_x * TILE_SIZE;
	game->player->y = game->data->player_y * TILE_SIZE;
	game->player->tile_x = game->data->player_x;
	game->player->tile_y = game->data->player_y;

	// init start direction on pi
	if (game->data->player_direction == 'N')
		game->player->direction = M_PI;
	else if (game->data->player_direction == 'S')
		game->player->direction = M_PI / 2;
	else if (game->data->player_direction == 'E')
		game->player->direction = M_PI / 4;
	else if (game->data->player_direction == 'W')
		game->player->direction = M_PI * 3 / 4;
}

void init(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return ; // add an exit + free all
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		return ; // add an exit + free all
	// check and malloc complete

	init_player(game);
	game->mlx = mlx_init(WIN_HEIGHT, WIN_WIDTH, "Cube3D", 0);
	// debug 2d
	init_map(game); // 2d map
	//debug_player(game); // 2d player  ne need we'll render it virtually from the raycasting
}
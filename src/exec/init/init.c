
#include "../../../include/cube3d.h"

// Main initialization function

// init the struct player
void init_player(t_game *game) {
	game->player->x = game->data->player_x * TILE_SIZE + TILE_SIZE / 2;
	game->player->y = game->data->player_y * TILE_SIZE + TILE_SIZE / 2;
	game->player->tile_x = game->data->player_x;
	game->player->tile_y = game->data->player_y;

	// init start direction on pi
	if (game->data->player_direction == 'N')
		game->player->direction = (3 * M_PI) / 2;
	else if (game->data->player_direction == 'S')
		game->player->direction = M_PI / 2;
	else if (game->data->player_direction == 'E')
		game->player->direction = 0;
	else if (game->data->player_direction == 'W')
		game->player->direction = M_PI;
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
	game->ray->fov_rd = (FOV * M_PI) / 180; // field of view in radians
	// get map sizes
	game->map_h = map_height(game->data->map);
	game->map_w = map_width(game->data->map);

	init_player(game);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3D", 1);
	// debug 2d
	init_map(game); // 2d map
	//debug_player(game); // 2d player  ne need we'll render it virtually from the raycasting
}
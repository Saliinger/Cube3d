#include "../../include/cube3d.h"

// doc
// step_x / step_y = position of the wall

// one ray = line of the fov
// fov = 60deg

// S_W = win-w
// s_h = win-h

// the first ray is the far left one
// so it goes from the left to the right

// ray angle = player_angle on PI - FOV(60) + x
// x is the n of the fov(60)

// the inter is the hit of the tiles that i am in from the player to the wall of the tiles and depending of that we can calculate to line through the wall
// height_inter = (player_y / TILE_SIZE) * TILE_SIZE
// width_inter = player_x * (height_inter - player_y) / tan(ray_angle)
// the ray angle is the angle that we're trying to cast so for exemple the far left one is 1deg from the camera angle

// step_y = TILE_SIZE
// step_x = TILESIZE / tan(ray_angle)

void set_ray(t_game *game, int ray_angle)
{
	int angl = game->player->angl - FOV + ray_angle;
	game->ray->inter_x = game->player->x * (game->ray->inter_y - game->player->y) / tan(angl);
	game->ray->inter_y = game->player->y;
	game->ray->step_x = game->ray->inter_x / tan(angl);
	game->ray->step_y = TILE_SIZE;
}

void raycasting(t_game *game)
{
	int x = 0;

	while (x < FOV)
	{
		set_ray(game, x);
		x++;
	}
}
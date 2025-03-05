#include "../../../include/exec.h"

void					init(t_game *game)
{
	int error;

	error = init_texture(game);
	error += init_window(game);
	error += init_player(game);
	error += init_ray(game);
	game->fov_rad = FOV * M_PI / 180;
	if (error > 0)
		exit(1); // add nuke there
}
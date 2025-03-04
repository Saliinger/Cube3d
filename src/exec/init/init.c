#include "../../../include/exec.h"

int					init(t_game *game)
{
	int error;

	error = init_texture(game);
	error += init_image(game);
	error += init_player(game);
	error += init_ray(game);
	if (error > 0)
		exit(1); // add nuke there
	return (0);
}
#include "../../../include/cube3d.h"

void left_right(t_game *game, int i)
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
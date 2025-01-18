#include "../../../include/cube3d.h"

void wasd(t_game *game, enum e_direction direction)
{
	if (direction == w)
          game->player->y -= 1;
	else if (direction == w)
		game->player->y += 1;
	else if (direction == a)
		game->player->x -= 1;
	else if (direction == d)
		game->player->x += 1;
}
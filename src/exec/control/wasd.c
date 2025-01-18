#include "../../../include/cube3d.h"

void wasd(t_game *game, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_W)
          game->player->y += 1;
	else if (key.key == MLX_KEY_A)
		game->player->x -= 1;
	else if (key.key == MLX_KEY_S)
		game->player->y -= 1;
	else if (key.key == MLX_KEY_D)
		game->player->x += 1;
    game->player_img->instances->x = game->player->x;
    game->player_img->instances->y = game->player->y;
}
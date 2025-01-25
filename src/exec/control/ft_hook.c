#include "../../../include/cube3d.h"

void	ft_reles(mlx_key_data_t keydata, t_game *game)	// release the key
{
  if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE)) // move left
    game->player->move_ad = 0;
  else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE)) // move right
    game->player->move_ad = 0;
  else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE)) // move down
    game->player->move_ws = 0;
  else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE) // move up
    game->player->move_ws = 0;
  else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE) // rotate left
    game->player->move_lr = 0;
  else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE) // rotate right
    game->player->move_lr = 0;
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
  t_game *game = (t_game *)param;

  if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
    //ft_exit(mlx);
      exit(0);
  else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
    game->player->move_ad = -1;
  else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
    game->player->move_ad = 1;
  else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
    game->player->move_ws = -1;
  else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
    game->player->move_ws = 1;
  else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
    game->player->move_lr = -1;
  else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
    game->player->move_lr = 1;
  ft_reles(keydata, game); // release the key
}

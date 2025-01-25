#include "../../../include/cube3d.h"

static void	key_handler(mlx_key_data_t keydata, t_game *data)
{
  if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
  {
    // add free game
    exit(0);
  }
  if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT) && keydata.action == MLX_PRESS) {
    if (keydata.key == MLX_KEY_RIGHT)
      left_right(data, 1);
    else
      left_right(data, 0);
  }
  if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_W) && keydata.action == MLX_PRESS)
    wasd(data, keydata); // need to add an on relase function
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
  t_game *game = (t_game *)param;

  key_handler(keydata, game);
}

#include "../../../include/cube3d.h"

static void	key_handler(mlx_key_data_t keydata, t_game *data)
{
  if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
  {
    // add free game
    exit(0);
  }
  if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
    left_right(data);
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
  t_game *game = (t_game *)param;

  key_handler(keydata, game);
}

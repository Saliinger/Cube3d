#include "../../../include/exec.h"

void raycasting(t_game *game)
{
  int x;
  float wall_x;
  float wall_y;

  x = 0;
  wall_x = 0;
  wall_y = 0;
  game->rayon->angle = normalize_angle(game->player->angle - game->fov_rad / 2);
  while (x < WIN_WIDTH)
  {
    wall_x = inter_x(game->rayon);
    wall_y = inter_y(game->rayon);

    if (wall_y <= wall_x)
      game->rayon->wall_distance = wall_x;
    else
      game->rayon->wall_distance = wall_y;

    // add the wall render there
    x++;
    game->rayon->angle += game->fov_rad / WIN_WIDTH;
  }
}
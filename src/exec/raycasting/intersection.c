#include "../../../include/exec.h"

static void init_delta(t_game *game, float *delta_x, float *delta_y, char flag)
{
  if (flag == 'x')
  {
    *delta_x = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
    *delta_y = game->player->x + (*delta_x - game->player->y) / tan(game->rayon->angle);
  }
  if (flag == 'y')
  {
    *delta_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
    *delta_y = game->player->y + (*delta_x - game->player->x) / tan(game->rayon->angle);
  }
}

float inter_x(t_rayon *ray)
{
  float delta_x;
  float delta_y;
  float step_x;
  float step_y;

  init_delta(ray, &delta_x, &delta_y, 'x');
  step_x = delta_x / TILE_SIZE;
  step_y = delta_y / TILE_SIZE;


  return 0;
}

float inter_y(t_rayon *ray)
{
  float delta_x;
  float delta_y;
  float step_x;
  float step_y;

  init_delta(ray, &delta_x, &delta_y, 'y');
  step_x = delta_x / TILE_SIZE;
  step_y = delta_y / TILE_SIZE;

  return 0;
}


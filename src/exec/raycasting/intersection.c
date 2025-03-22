#include "../../../include/exec.h"

static void init_delta(t_game *game, float *delta_x, float *delta_y, char flag)
{
  if (flag == 'x')
  {
    *delta_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
    *delta_y = game->player->y + (*delta_x - game->player->x) / tan(game->rayon->angle);
  }
  if (flag == 'y')
  {
    *delta_x = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
    *delta_y = game->player->x + (*delta_x - game->player->y) / tan(game->rayon->angle);
  }
}

float inter_x(t_game *game, t_rayon *ray)
{
  float delta_x;
  float delta_y;
  float step_x;
  float step_y;

  init_delta(game, &delta_x, &delta_y, 'x');
<<<<<<< HEAD
  step_x = TILE_SIZE / tan(ray->angle);
  step_y = TILE_SIZE;
  while (wall_hit(game->window->map, delta_x, delta_y))
=======
  step_x = TILE_SIZE;
  step_y = TILE_SIZE / tan(ray->angle);
  while(wall_hit(game, game->window->map, step_x, step_y))
>>>>>>> 625534bd5667920def00baa02f7300752d0fe39c
  {
    delta_x += step_x;
    delta_y += step_y;
  }
<<<<<<< HEAD
  ray->x_x = delta_x;
  ray->x_y = delta_y;
=======
>>>>>>> 625534bd5667920def00baa02f7300752d0fe39c
  return (sqrt(pow(delta_x - game->player->x, 2) + pow(delta_y - game->player->y, 2)));
}

float inter_y(t_game *game, t_rayon *ray)
{
  float delta_x;
  float delta_y;
  float step_x;
  float step_y;

  init_delta(game, &delta_x, &delta_y, 'y');
<<<<<<< HEAD
  step_x = TILE_SIZE;
  step_y = TILE_SIZE / tan(ray->angle);
  while (wall_hit(game->window->map, delta_x, delta_y))
=======
  step_x = TILE_SIZE / tan(ray->angle);
  step_y = TILE_SIZE;

  while(wall_hit(game, game->window->map, step_x, step_y))
>>>>>>> 625534bd5667920def00baa02f7300752d0fe39c
  {
    delta_x += step_x;
    delta_y += step_y;
  }
<<<<<<< HEAD
  ray->y_x = delta_x;
  ray->y_y = delta_y;
=======
>>>>>>> 625534bd5667920def00baa02f7300752d0fe39c
  return (sqrt(pow(delta_x - game->player->x, 2) + pow(delta_y - game->player->y, 2)));
}



#include "../../../include/exec.h"

int init_ray(t_game *game)
{
  t_rayon			*ray;
  ray = (t_rayon *)malloc(sizeof(t_rayon));
  if (!ray)
    return (1);
  // add 0 value
  game->rayon = ray;
  return (0);
}
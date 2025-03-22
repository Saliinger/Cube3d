#include "../../../include/exec.h"

int wall_hit(t_game *game, char **map, float x, float y)
{
  int grid_x;
  int grid_y;

  grid_x = floor(x / TILE_SIZE);
  grid_y = floor(y / TILE_SIZE);
  if (grid_x > game->window->map_width || grid_y > game->window->map_height || grid_x < 0 || grid_y < 0)
    return (1);
  if (map[grid_y][grid_x] == '1')
    return (1);
  return (0);
}
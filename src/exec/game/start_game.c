#include "../../../include/exec.h"

void		start_game(t_game *game)
{
  // loop for movement there
  // loop for rendering
  if (DEBUG)
    map_debug(game);
  mlx_loop(game->window->mlx);
}
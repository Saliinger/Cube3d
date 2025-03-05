#include "../../../include/exec.h"

int init_player(t_game *game)
{
  t_player	*player;

  player = malloc(sizeof(t_player));
  if (!player)
    return (1);
  player->x = game->data->player_x;
  player->y = game->data->player_y;
  player->angle = M_PI / 2; // need to add a selector
  game->player = player;
  return (0);
}
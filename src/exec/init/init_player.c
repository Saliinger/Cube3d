#include "../../../include/exec.h"

int init_player(t_game *game)
{
  t_player	*player;

  player = malloc(sizeof(t_player));
  if (!player)
    return (1);
  player->x = game->data->player_x;
  player->y = game->data->player_y;
  player->angle = game->data->player_direction;
  game->player = player;
  return (0);
}
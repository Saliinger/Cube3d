#include "../../../include/exec.h"

int	init_texture(t_game *game)
{
  t_texture	*texture;

  texture = malloc(sizeof(t_texture));
  if (!texture)
    return (1);
  texture->nord = mlx_load_png(game->data->no_texture);
  texture->sud = mlx_load_png(game->data->so_texture);
  texture->est = mlx_load_png(game->data->ea_texture);
  texture->ouest = mlx_load_png(game->data->we_texture);
  if (!texture->nord || !texture->sud || !texture->est || !texture->ouest)
    return (1);
  game->texture = texture;
  return (0);
}

int					init_window(t_game *game)
{
  t_window	*window;

  window = malloc(sizeof(t_window));
  if (!window)
    return (1);
  window->fpv = mlx_new_image(game->window->mlx, WIN_WIDTH, WIN_HEIGHT);
  if (!window->fpv)
    return (1);
  window->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3D" , 1);
  if (!window->mlx)
    return (1);
  window->map = game->data->map;
  window->map_width = map_width(window->map);
  window->map_height = map_height(window->map);
  game->window = window;
  return (0);
}

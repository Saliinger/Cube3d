#include "../../../include/cube3d.h"

mlx_image_t *load_image(t_game *game, char *path)
{
	mlx_image_t *image;
	mlx_texture_t *texture;

	texture = mlx_load_png(path);
	if (!texture)
		ft_error("Error\npng didn't load\n");
	image = mlx_texture_to_image(game->mlx, texture);
	if (!image)
		ft_error("Error\npng didn't load\n");
	return (image);
}

void init(t_game *game)
{
	printf("init\n%s\n%s\n%s\n%s\n", game->data->no_texture, game->data->so_texture, game->data->ea_texture, game->data->we_texture);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3d", true);
	game->n = load_image(game, game->data->no_texture);
	game->s = load_image(game, game->data->so_texture);
	game->e = load_image(game, game->data->ea_texture);
	game->w = load_image(game, game->data->we_texture);
}
#include "../../../include/cube3d.h"

mlx_image_t *load_image(t_game *game, char *path)
{
	mlx_image_t *image;
	mlx_texture_t *texture;

	texture = mlx_load_png(path);
	if (!texture)
    {
         printf("path: %s\n", path);
		ft_error("Error\npng didn't load\n");
    }
	image = mlx_texture_to_image(game->mlx, texture);
	if (!image)
	{
        printf("path: %s\n", path);
		ft_error("Error\npng didn't load\n");
    }
	return (image);
}

void init_img(t_game *game)
{
	printf("init\n%s\n%s\n%s\n%s\n", game->data->no_texture, game->data->so_texture, game->data->ea_texture, game->data->we_texture);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3d", true);
	game->n = load_image(game, game->data->no_texture);
	game->s = load_image(game, game->data->so_texture);
	game->e = load_image(game, game->data->ea_texture);
	game->w = load_image(game, game->data->we_texture);
}

void	init_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	char **map = game->data->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == '1')
				mlx_image_to_window(game->mlx, game->n, j * TILE_SIZE, i
					* TILE_SIZE);
            else if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'N')
				mlx_image_to_window(game->mlx, game->e, j * TILE_SIZE, i
					* TILE_SIZE);

			j++;
		}
		i++;
	}
}

void debug_player(t_game *game)
{
	mlx_image_t *image;
//	mlx_texture_t *texture;
//    char *path = "./assets/pillar.png";

//	texture = mlx_load_png(path);
//	if (!texture)
//		ft_error("1Error\npng didn't load\n");
	image = mlx_new_image(game->mlx, TILE_SIZE / 2, TILE_SIZE / 2);
	if (!image)
		ft_error("1Error\npng didn't load\n");
    int i;
    int j;
    i = 0;
    while (i < TILE_SIZE / 2)
      {
      j = 0;
      while (j < TILE_SIZE / 2)
      {
        mlx_put_pixel(image, i, j, 0xFFFFFF);
        j++;
      }
      i++;
      }

    mlx_image_to_window(game->mlx, image, game->data->player_x, game->data->player_y);
    game->player_img = image;
}

void init(t_game *game)
{
	init_img(game); // not gonna be used for now
	// add img to window for map
	init_map(game);
    debug_player(game);
}


//else if (map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'N')
//				mlx_image_to_window(game->mlx, game->w, j * TILE_SIZE, i
//					* TILE_SIZE);
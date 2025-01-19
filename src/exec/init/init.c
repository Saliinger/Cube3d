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
	//printf("init\n%s\n%s\n%s\n%s\n", game->data->no_texture, game->data->so_texture, game->data->ea_texture, game->data->we_texture);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3d", true);
	game->n = load_image(game, game->data->no_texture);
	game->s = load_image(game, game->data->so_texture);
	game->e = load_image(game, game->data->ea_texture);
	game->w = load_image(game, game->data->we_texture);
}

mlx_image_t	*cube(t_game *game, uint32_t color)
{
	mlx_image_t *image;
	int i = 0;
	int j;

	image = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(image, i, j, color);
			j++;
		}
		i++;
	}
	return (image);
}

uint32_t rgb_to_hex(int red, int green, int blue) {
	// Vérification que les valeurs sont dans la plage valide
	if (red < 0 || red > 255 ||
	    green < 0 || green > 255 ||
	    blue < 0 || blue > 255) {
		fprintf(stderr, "Erreur: Les valeurs RGB doivent être entre 0 et 255\n");
		return 0;
	}

	// Conversion en format hexadécimal
	// On décale les bits et on combine les valeurs
	// L'alpha (0xFF) est ajouté à la fin
	uint32_t hex = ((uint32_t)red << 24) |    // Rouge dans les bits 31-24
	               ((uint32_t)green << 16) |   // Vert dans les bits 23-16
	               ((uint32_t)blue << 8) |     // Bleu dans les bits 15-8
	               0xFF;                       // Alpha (255) dans les bits 7-0

	return hex;
}

void    init_map(t_game *game)
{
	int    i;
	int    j;
	int    border;
	mlx_image_t *white_img;
	mlx_image_t *black_img;

	white_img = cube(game, rgb_to_hex(255, 255, 255));
	black_img = cube(game, rgb_to_hex(0, 0, 0));
	border = 2;
	i = 0;
	char **map = game->data->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] != ' ')
				mlx_image_to_window(game->mlx, black_img, j * TILE_SIZE, i * TILE_SIZE);
			if (map[i][j] == '1')
				mlx_image_to_window(game->mlx, black_img, j * TILE_SIZE + border, i * TILE_SIZE + border);
			else if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'N')
				mlx_image_to_window(game->mlx, white_img, j * TILE_SIZE + border, i * TILE_SIZE + border);
			j++;
		}
		i++;
	}
}

void debug_player(t_game *game)
{
	mlx_image_t *image;

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
			mlx_put_pixel(image, i, j, rgb_to_hex(255, 0, 0));
			j++;
		}
		i++;
	}
	printf("player\n%d %d\n", game->data->player_x, game->data->player_y);
    mlx_image_to_window(game->mlx, image, game->data->player_x * TILE_SIZE,game->data->player_y * TILE_SIZE);
    game->player_img = image;
}

void init(t_game *game)
{
	init_img(game);
	// debug features
	init_map(game);
    debug_player(game);
	// debug features
}


//else if (map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'N')
//				mlx_image_to_window(game->mlx, game->w, j * TILE_SIZE, i
//					* TILE_SIZE);
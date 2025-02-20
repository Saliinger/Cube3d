#include "../../../include/cube3d.h"

static uint32_t rgb_to_hex(int red, int green, int blue) {
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

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;
    int floor;
    int ceiling;

	floor = rgb_to_hex(game->data->floor[0], game->data->floor[1], game->data->floor[2]);
    ceiling = rgb_to_hex(game->data->ceiling[0], game->data->ceiling[1], game->data->ceiling[2]);
	i = b_pix;

	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(game, ray, i++, floor); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, ceiling); // ceiling
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}


double	get_x_o(mlx_texture_t	*texture, t_game *game)
{
	double	x_o;

	if (game->ray->flag == 1)
		x_o = (int)fmodf((game->ray->horiz_x * (texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((game->ray->vert_y * (texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}

void	draw_wall(t_game *game, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(game, game->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, game);
	y_o = (t_pix - (WIN_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(game, (int)game->ray->index, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
        t_pix++;
	}
}

void	render_wall(t_game *game, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray->wall_dist *= cos(nor_angle(game->ray->ray_angle - game->player->direction)); // fix the fisheye
	wall_h = (TILE_SIZE / game->ray->wall_dist) * ((WIN_WIDTH / 2) / tan(game->ray->fov_rd / 2)); // get the wall height
	b_pix = (WIN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (WIN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > WIN_HEIGHT) // check the bottom pixel
		b_pix = WIN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	game->ray->index = ray;
	draw_floor_ceiling(game, ray, t_pix, b_pix); // draw the floor and the ceiling
	draw_wall(game, t_pix, b_pix, wall_h); // draw the wall
}
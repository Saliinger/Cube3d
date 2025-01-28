#include "../../../include/cube3d.h"

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
	draw_wall(game, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(game, ray, t_pix, b_pix); // draw the floor and the ceiling
}
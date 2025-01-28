#include "../../../include/cube3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)	// put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= WIN_WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= WIN_HEIGHT)
		return ;
	mlx_put_pixel(game->fpv, x, y, color); // put the pixel
}

int	get_color(t_game *game, int flag)	// get the color of the wall
{
	game->ray->ray_angle = nor_angle(game->ray->ray_angle); // normalize the angle
	if (flag == 0)
	{
		if (game->ray->ray_angle > M_PI / 2 && game->ray->ray_angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (game->ray->ray_angle > 0 && game->ray->ray_angle < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void	draw_wall(t_game *game, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;

	color = get_color(game, game->ray->flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(game, ray, t_pix++, color);
}

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;

	i = b_pix;
	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(game, ray, i++, 0xB99470FF); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, 0x89CFF3FF); // ceiling
}


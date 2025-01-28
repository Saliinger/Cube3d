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

// get the texture of the wall by checking the flag to know if it's a north/sud or east west wall then use a furmula to choose wich one it's'
mlx_texture_t *get_texture(t_game *game, int flag)
{
  	int angle = nor_angle(game->ray->ray_angle);
	if (flag == 0)
	{
		if (angle > M_PI / 2 && angle < 3 * (M_PI / 2))
           return (game->texture->ea);
        else
          return (game->texture->we);
	}
	else
	{
		if (angle > 0 && angle < M_PI)
			return (game->texture->so);
		else
			return (game->texture->no);
	}
}


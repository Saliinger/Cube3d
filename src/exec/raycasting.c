#include "../../include/cube3d.h"

// doc
// step_x / step_y = position of the wall

// one ray = line of the fov
// fov = 60deg

// S_W = win-w
// s_h = win-h

// the first ray is the far left one
// so it goes from the left to the right

// ray angle = player_angle on PI - FOV(60) + x
// x is the n of the fov(60)

// the inter is the hit of the tiles that i am in from the player to the wall of the tiles
// and depending of that we can calculate to line through the wall
// height_inter = (player_y / TILE_SIZE) * TILE_SIZE
// width_inter = player_x * (height_inter - player_y) / tan(ray_angle)
// the ray angle is the angle that we're trying to cast so for exemple the far left one is 1deg from the camera angle

// step_y = TILE_SIZE
// step_x = TILESIZE / tan(ray_angle)


// the ray go from the virtual player position to the inter x/y that touch the wall the step x/y are used to detect the wall


// circle unit is to check if the unit is in the range

// draw the ray on the fpv img based on the player position


int	unit_circle(float angle, char c)	// check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_game *game)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if (y_m >= game->map_h || x_m >= game->map_w)
		return (0);
	if (game->data->map[y_m] && x_m <= (int)ft_strlen(game->data->map[y_m]))
		if (game->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float inter_h(t_game *game) {
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(game->ray->ray_angle);
	h_y = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(game->ray->ray_angle, &h_y, &y_step, 1);
	h_x = game->player->x + (h_y - game->player->y) / tan(game->ray->ray_angle);
	if ((unit_circle(game->ray->ray_angle, 'y') && x_step > 0) || (!unit_circle(game->ray->ray_angle, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, game)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - game->player->x, 2) + pow(h_y - game->player->y, 2))); // get the distance
}

float inter_w(t_game *game) {
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(game->ray->ray_angle);
	v_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(game->ray->ray_angle, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = game->player->y + (v_x - game->player->y) * tan(game->ray->ray_angle);
	if ((unit_circle(game->ray->ray_angle, 'x') && y_step < 0) || (!unit_circle(game->ray->ray_angle, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, game)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - game->player->x, 2) + pow(v_y - game->player->y, 2))); // get the distance
}

void draw_ray(t_game *game)
{
	float hit_x; // Intersection X coordinate
	float hit_y; // Intersection Y coordinate
	float h_inter = inter_h(game); // Horizontal wall distance
	float v_inter = inter_w(game); // Vertical wall distance

	// Determine the closer intersection point
	if (v_inter <= h_inter)
	{
		// Vertical wall hit
		hit_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE; // Adjusted vertical intersection X
		hit_y = game->player->y + (hit_x - game->player->x) * tan(game->ray->ray_angle); // Corresponding Y
	}
	else
	{
		// Horizontal wall hit
		hit_y = floor(game->player->y / TILE_SIZE) * TILE_SIZE; // Adjusted horizontal intersection Y
		hit_x = game->player->x + (hit_y - game->player->y) / tan(game->ray->ray_angle); // Corresponding X
	}

	// Draw the ray from player's position to the wall hit
	float ray_x = game->player->x;
	float ray_y = game->player->y;

	// Bresenham's line algorithm or per-pixel plotting
	while ((int)ray_x != (int)hit_x || (int)ray_y != (int)hit_y) {
		mlx_put_pixel(game->fpv, (int)ray_x, (int)ray_y, 0xFF0000); // Draw ray with a red color
		ray_x += (hit_x - ray_x) * 0.01; // Increment along the ray direction
		ray_y += (hit_y - ray_y) * 0.01;
	}
	printf("x: %f\ny: %f\n", hit_x, hit_y);
}

void raycasting(t_game *game)
{
	int x = 0;
	float h_inter;
	float v_inter;

	game->ray->ray_angle = game->player->direction - (FOV / 2);
	// fov is used to render the 2d top view the WIN_WIDTH will be used for the 2.5d render to scale it to the window
	while (x < FOV)
	{
		game->ray->flag = 0;
		h_inter = inter_h(game);
		v_inter = inter_w(game);
		if (v_inter <= h_inter) {
			game->ray->wall_dist = v_inter;
		}
		else {
			game->ray->wall_dist = h_inter;
			game->ray->flag = 1;
		}
		// it's for the 2d debug need to make the texture rendering
		draw_ray(game);
		x++;
		game->ray->ray_angle += (FOV / 2); // 1deg
	}
}
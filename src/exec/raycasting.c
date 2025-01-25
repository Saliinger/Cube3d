#include "../../include/cube3d.h"

// doc
// step_x / step_y = position of the wall

// one ray = line of the fov
// fov = 60deg

// WIN_WIDTH = win-w
// WIN_HEIGHT = win-h

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

float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

// test render wall


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

// test render wall

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

int	inter_check(float angle, float *inter, float *step, int iWIN_HEIGHTorizon)	// check the intersection
{
	if (iWIN_HEIGHTorizon)
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
    float h_x, h_y, x_step, y_step;
    int pixel;
    float angle;

    angle = nor_angle(game->ray->ray_angle);
    y_step = TILE_SIZE;
    x_step = TILE_SIZE / tan(angle);
    h_y = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angle, &h_y, &y_step, 1);
    h_x = game->player->x + (h_y - game->player->y) / tan(angle);
    if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
        x_step *= -1;

    // Iterate until a wall is hit or out of bounds
    while (wall_hit(h_x, h_y - pixel, game)) {
        h_x += x_step;
        h_y += y_step;
    }

    return sqrt(pow(h_x - game->player->x, 2) + pow(h_y - game->player->y, 2));
}

float inter_w(t_game *game) {
    float v_x, v_y, x_step, y_step;
    int pixel;
    float angle;

    angle = nor_angle(game->ray->ray_angle);
    x_step = TILE_SIZE;
    y_step = TILE_SIZE * tan(angle);
    v_x = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angle, &v_x, &x_step, 0);
    v_y = game->player->y + (v_x - game->player->x) * tan(angle);
    if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0))
        y_step *= -1;

    // Iterate until a wall is hit or out of bounds
    while (wall_hit(v_x - pixel, v_y, game)) {
        v_x += x_step;
        v_y += y_step;
    }

    return sqrt(pow(v_x - game->player->x, 2) + pow(v_y - game->player->y, 2));
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color) {
    // Clip coordinates to screen bounds
    if (x0 < 0 || x0 >= WIN_WIDTH || y0 < 0 || y0 >= WIN_HEIGHT ||
        x1 < 0 || x1 >= WIN_WIDTH || y1 < 0 || y1 >= WIN_HEIGHT)
        return;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_put_pixel(game->fpv, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void raycasting(t_game *game) {
    int x = 0;
    float h_inter, v_inter;

    // Convert FOV to radians for calculations
    game->ray->fov_rd = FOV * (M_PI / 180.0);
    game->ray->ray_angle = game->player->direction - (game->ray->fov_rd / 2);

    while (x < WIN_WIDTH) {
        game->ray->flag = 0;
        h_inter = inter_h(game);
        v_inter = inter_w(game);

        // Use the shortest intersection distance
        if (v_inter <= h_inter) {
            game->ray->wall_dist = v_inter;
        } else {
            game->ray->wall_dist = h_inter;
            game->ray->flag = 1;
        }

        // // Visualize the ray for debugging
        // float ray_x = game->player->x + cos(nor_angle(game->ray->ray_angle)) * game->ray->wall_dist;
        // float ray_y = game->player->y + sin(nor_angle(game->ray->ray_angle)) * game->ray->wall_dist;
        // draw_line(game, game->player->x, game->player->y, ray_x, ray_y, 0xFFFFFF);
        //
        // // Debugging output
        // printf("Ray %d: Angle=%.2f, Dist=%.2f, RayX=%.2f, RayY=%.2f\n",
        //        x, game->ray->ray_angle, game->ray->wall_dist, ray_x, ray_y);
    	render_wall(game, x);

        // Increment ray angle
        game->ray->ray_angle = nor_angle(game->ray->ray_angle + (game->ray->fov_rd / WIN_WIDTH));
        x++;
    }
}

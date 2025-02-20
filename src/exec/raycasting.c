#include "../../include/cube3d.h"

// put the angle on 0 to 180
int	unit_circle(float angle, char c)
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

// check intersection
// increase the inter if the angle is is in tolerance and remove one step
int	inter_check(float angle, float *inter, float *step, int is_horizon)
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

// check if the ray hit a wall
int	wall_hit(float x, float y, t_game *game)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if (y_m >= game->map_h || x_m >= game->map_w)
		return (0);
	if (game->data->map[y_m] && x_m <= (int)ft_strlen(game->data->map[y_m]))
		if (game->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}


// inter height
// get the wall hit on the height
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
	while (wall_hit(h_x, h_y - pixel, game))
    {
        h_x += x_step;
        h_y += y_step;
    }

	game->ray->horiz_x = h_x;
	game->ray->horiz_y = h_y;
    return sqrt(pow(h_x - game->player->x, 2) + pow(h_y - game->player->y, 2));
}

// inter width
// get the wall hit on the width
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
    while (wall_hit(v_x - pixel, v_y, game))
    {
        v_x += x_step;
        v_y += y_step;
    }
	game->ray->vert_x = v_x;
	game->ray->vert_y = v_y;
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

    while (1)
    {
        mlx_put_pixel(game->fpv, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// the raycasting iterate through each pixel of the window width to get every wall distance
void raycasting(t_game *game)
{
    int x = 0;
    float h_inter, v_inter;

    game->ray->ray_angle = game->player->direction - (game->ray->fov_rd / 2);
    while (x < WIN_WIDTH)
    {
        game->ray->flag = 0;
        h_inter = inter_h(game);
        v_inter = inter_w(game);
    	if (v_inter <= h_inter)
            game->ray->wall_dist = v_inter;
        else
        {
            game->ray->wall_dist = h_inter;
            game->ray->flag = 1;
        }
    	render_wall(game, x);

    	// float ray_x = game->player->x + cos(nor_angle(game->ray->ray_angle)) * game->ray->wall_dist;
    	// float ray_y = game->player->y + sin(nor_angle(game->ray->ray_angle)) * game->ray->wall_dist;
    	// draw_line(game, game->player->x, game->player->y, ray_x, ray_y, 0xFFFFFF);

        game->ray->ray_angle = game->ray->ray_angle + (game->ray->fov_rd / WIN_WIDTH);
        x++;
    }
}


// // Visualize the ray for debugging

//
// // Debugging output
// printf("Ray %d: Angle=%.2f, Dist=%.2f, RayX=%.2f, RayY=%.2f\n",
//        x, game->ray->ray_angle, game->ray->wall_dist, ray_x, ray_y);

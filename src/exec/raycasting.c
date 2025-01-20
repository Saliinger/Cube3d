#include "../../include/cube3d.h"

/*
We initialize the set up for the rays
- camera_x -> Where is the camera (-1 = left, 0 = center, 1 = right)
- dir_x/y = direction of the ray
- map_x/y = current square of the ray
- deltadist_x/y = distance to go to the next x or y.
*/

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

static void	init_raycasting_info(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

/*
- We are doing the initial set up for the dda
- dda algorithm will jump one square in each loop eiter in a x or y direction
- ray->sidedist_x or y = distance from the ray start position to the
	next x or y position
- if x or y < 0 go the next x or y to the left
- if x or y > 0 go the next x or y to the right
*/

static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

/*
- We implement the DDA algorithm -> the loop will increment 1 square
-   until we hit a wall
- If the sidedistx < sidedisty, x is the closest point from the ray
*/

static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
		    || ray->map_x < 0.25
		    || ray->map_y > 5 - 0.25 // a modifie pour la taille de la map h
		    || ray->map_x > 5 - 1.25)// a modifie pour la taille de la map w
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

static void	calculate_line_height(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT  / 2;
	if (ray->draw_end >= WIN_HEIGHT )
		ray->draw_end = WIN_HEIGHT  - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

/* Helper function to draw a line (ray) on the screen */
static void draw_line_to_img(void *img, double x1, double y1, double x2, double y2, int color)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	double x_inc = dx / steps;
	double y_inc = dy / steps;
	double x = x1;
	double y = y1;

	for (int i = 0; i <= steps; i++)
	{
		// Only draw the pixel if it is within screen bounds
		if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		{
			mlx_put_pixel(img, (int)round(x), (int)round(y), color);
		}
		x += x_inc;
		y += y_inc;
	}
}

/* Function to draw rays for visualizing player's FOV and wall collisions */
void draw_rays(t_game *game)
{
	t_ray   ray;
	int     x;

	x = 0;
	ray = *game->ray;

	// Ensure the game structures are initialized
	if (!game || !game->player || !game->ray || !game->player_img)
	{
		fprintf(stderr, "Error: Missing game, player, ray, or player_img initialization.\n");
		return;
	}

	// Iterate over the width of the screen (FOV rendering)
	while (x < WIN_WIDTH)
	{
		// Initialize raycasting variables
		init_raycasting_info(x, &ray, game->player);
		set_dda(&ray, game->player);
		perform_dda(game->data, &ray);
		calculate_line_height(&ray, game->player);

		// Determine the endpoint of the ray (wall hit point)
		double ray_end_x = game->player->pos_x + ray.dir_x * ray.wall_dist;
		double ray_end_y = game->player->pos_y + ray.dir_y * ray.wall_dist;

		// Draw the ray from player's position to the wall collision point
		draw_line_to_img(game->player_img,
		                 game->player->pos_x * TILE_SIZE,  // Scale position to match display
		                 game->player->pos_y * TILE_SIZE,
		                 ray_end_x * TILE_SIZE,
		                 ray_end_y * TILE_SIZE,
		                 0xFFFFFF); // Ray color (white)
		x++;
	}
}

/* Updated raycasting function to include drawing */
void raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = *game->ray;

	// Ensure the game structures are initialized
	if (!game || !game->player || !game->ray || !game->player_img)
	{
		fprintf(stderr, "Error: Missing game, player, ray, or player_img initialization.\n");
		return;
	}

	while (x < WIN_WIDTH)
	{
		init_raycasting_info(x, &ray, game->player);
		set_dda(&ray, game->player);
		perform_dda(game->data, &ray);
		calculate_line_height(&ray, game->player);

		x++;
	}

	// Draw rays after raycasting is complete
	draw_rays(game);
}
#include <math.h>
#include "../../include/cube3d.h"

//void init_ray(t_ray *ray)
//{
//	ray->pos_x = 0;
//	ray->pos_y = 0;
//	ray->dir_x = 0;
//	ray->dir_y = 0;
//	ray->plane_x = 0;
//	ray->plane_y = 0;
//	ray->map_x = 0;
//	ray->map_y = 0;
//	ray->side = 0;
//	ray->wall_dist = 0;
//	ray->line_height = 0;
//	ray->draw_start = 0;
//	ray->draw_end = 0;
//	ray->wall_x = 0;
//	ray->deltadist_x = 0;
//}
//
//void set_ray(int x, t_game *game)
//{
//	game->ray = malloc(sizeof(t_ray));
//	init_ray(game->ray);
//	game->ray->pos_x = game->player->x;
//	game->ray->pos_y = game->player->y;
//	game->ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
//	game->ray->dir_x = game->ray->dir_x + game->ray->plane_x * game->ray->camera_x;
//	game->ray->dir_y = game->ray->dir_y + game->ray->plane_y * game->ray->camera_x;
//	game->ray->map_x = (int)game->ray->pos_x;
//	game->ray->map_y = (int)game->ray->pos_y;
//	game->ray->deltadist_x = fabs(1 / game->ray->dir_x);
//	game->ray->deltadist_y = fabs(1 / game->ray->dir_y);
//}
//
//static void	set_dda(t_ray *ray, t_game *game)
//{
//	if (ray->dir_x < 0)
//	{
//		ray->step_x = -1;
//		ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->deltadist_x;
//	}
//	else
//	{
//		ray->step_x = 1;
//		ray->sidedist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->deltadist_x;
//	}
//	if (ray->dir_y < 0)
//	{
//		ray->step_y = -1;
//		ray->sidedist_y = (game->ray->pos_y - ray->map_y) * ray->deltadist_y;
//	}
//	else
//	{
//		ray->step_y = 1;
//		ray->sidedist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->deltadist_y;
//	}
//}
//
//static void	perform_dda(t_game *game, t_ray *ray)
//{
//	int	hit;
//
//	hit = 0;
//	while (hit == 0)
//	{
//		if (ray->sidedist_x < ray->sidedist_y)
//		{
//			ray->sidedist_x += ray->deltadist_x;
//			ray->map_x += ray->step_x;
//			ray->side = 0;
//		}
//		else
//		{
//			ray->sidedist_y += ray->deltadist_y;
//			ray->map_y += ray->step_y;
//			ray->side = 1;
//		}
//		if (ray->map_y < 0.25 //add this part for collision
//		    || ray->map_x < 0.25
//		    || ray->map_y > game->map_h - 0.25
//		    || ray->map_x > game->map_w - 1.25)
//			break ;
//		else if (game->data->map[ray->map_y][ray->map_x] > '0')
//			hit = 1;
//	}
//}
//
//static void	calculate_line_height(t_ray *ray)
//{
//	if (ray->side == 0)
//		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
//	else
//		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
//	ray->line_height = (int)(WIN_HEIGHT/ ray->wall_dist);
//	ray->draw_start = -(ray->line_height) / 2 + WIN_HEIGHT / 2;
//	if (ray->draw_start < 0)
//		ray->draw_start = 0;
//	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
//	if (ray->draw_end >= WIN_HEIGHT)
//		ray->draw_end = WIN_HEIGHT - 1;
//	if (ray->side == 0)
//		ray->wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
//	else
//		ray->wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
//	ray->wall_x -= floor(ray->wall_x);
//}

void    draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;

	mlx_image_t *img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (1)
	{
		mlx_put_pixel(img,  x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
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
	mlx_image_to_window(game->mlx, img, game->player->x * TILE_SIZE, game->player->y *TILE_SIZE);
	//mlx_delete_image(game->mlx, img);
}

void raycasting(t_game *game)
{
//	int x = 0;

//	while (x < WIN_WIDTH)
//	{
//		set_ray(x, game);
//		set_dda(game->ray, game);
//		perform_dda(game, game->ray);
//		calculate_line_height(game->ray);
		draw_line(game, game->player->x, game->player->y, 100 + game->player->x, 100 + game->player->y, 0xFFFFFF);
//		x++;
//	}
}
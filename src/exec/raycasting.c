#include <math.h>
#include "../../include/exec.h"
#include "../../include/cube3d.h"

void raycasting(t_game *game)
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x, map_y;
	double side_dist_x, side_dist_y;
	double delta_dist_x, delta_dist_y, perp_wall_dist;
	int step_x, step_y;
	int hit, side;
	int line_height;
	int draw_start, draw_end;

	for (int x = 0; x < WIN_WIDTH; x++) {
		// Calculate ray position and direction
		camera_x = 2 * x / (double) WIN_WIDTH - 1;
		ray_dir_x = game->ray->dir_x + game->ray->plane_x * camera_x;
		ray_dir_y = game->ray->dir_y + game->ray->plane_y * camera_x;

		// Check where the ray starts on the map
		map_x = (int) game->player->x;
		map_y = (int) game->player->y;

		// Length of ray to next x or y side
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);

		// Calculate initial steps and distance to the first side
		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (game->player->x - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player->x) * delta_dist_x;
		}
		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (game->player->y - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player->y) * delta_dist_y;
		}

		// Perform DDA (Digital Differential Analysis)
		hit = 0;
		while (hit == 0) {
			// Jump to next map square in x or y direction
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// Check if ray hit a wall
			if (game->data->map[map_y][map_x] > 0) // Assuming map is a 2D array
				hit = 1;
		}

		// Calculate distance to the wall
		if (side == 0)
			perp_wall_dist = (map_x - game->player->x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player->y + (1 - step_y) / 2) / ray_dir_y;

		// Calculate line height based on distance
		line_height = (int) (WIN_HEIGHT / perp_wall_dist);

		// Calculate the start and end of the line to draw
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;
		//game->player_img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
		// Draw the pixel line on the screen for the specific x
		// You can implement a draw function using an mlx_image_t
		//int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF; // Lighter or darker color for sides
		for (int y = draw_start; y < draw_end; y++) {
			mlx_put_pixel(game->player_img, x, y, 0x00000);
		}

	}
	printf("raycasting\n");
}
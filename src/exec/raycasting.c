#include <math.h>
#include "../../include/cube3d.h"

void initialize_ray(t_game *game) {
	game->ray = malloc(sizeof(t_ray));
	if (game->ray == NULL) {
		perror("Error allocating ray structure");
		exit(EXIT_FAILURE);
	}
	// Initialize all ray fields to 0 (safe defaults)
	ft_memset(game->ray, 0, sizeof(t_ray));
}

void set_ray(int x, t_game *game) {
	// Calculate the position on the camera plane for the current ray
	game->ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;

	// Calculate ray direction based on player direction and FOV
	game->ray->dir_x = game->player->dir_x + game->ray->plane_x * game->ray->camera_x;
	game->ray->dir_y = game->player->dir_y + game->ray->plane_y * game->ray->camera_x;

	// Ensure that the ray starts from the player's current position
	game->ray->pos_x = game->player->x;
	game->ray->pos_y = game->player->y;

	// Map the player's position into grid coordinates
	game->ray->map_x = (int)game->ray->pos_x;
	game->ray->map_y = (int)game->ray->pos_y;

	// Calculate distances to the next grid line in each direction
	game->ray->deltadist_x = fabs(1 / game->ray->dir_x);
	game->ray->deltadist_y = fabs(1 / game->ray->dir_y);

	// Debug all values to verify correctness
	printf(
			"Ray %d => CameraX: %f, DirX: %f, DirY: %f, PosX: %f, PosY: %f, DeltaDistX: %f, DeltaDistY: %f\n",
			x, game->ray->camera_x, game->ray->dir_x, game->ray->dir_y,
			game->ray->pos_x, game->ray->pos_y, game->ray->deltadist_x, game->ray->deltadist_y
	);
}

void set_dda(t_ray *ray) {
	// Step in the X direction (+1 or -1)
	if (ray->dir_x < 0) {
		ray->step_x = -1;
		ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->deltadist_x;
	} else {
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->deltadist_x;
	}

	// Step in the Y direction (+1 or -1)
	if (ray->dir_y < 0) {
		ray->step_y = -1;
		ray->sidedist_y = (ray->pos_y - ray->map_y) * ray->deltadist_y;
	} else {
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->deltadist_y;
	}
}

void perform_dda(t_game *game, t_ray *ray) {
	int hit = 0; // Whether the ray hit a wall

	while (hit == 0) {
		if (ray->sidedist_x < ray->sidedist_y) {
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // Hit was a vertical wall
		} else {
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Hit was a horizontal wall
		}

		// Ensure map_x and map_y are within bounds
		if (ray->map_y < 0 || ray->map_y >= game->map_h ||
		    ray->map_x < 0 || ray->map_x >= game->map_w) {
			fprintf(stderr, "Ray out of bounds: map_x=%d, map_y=%d\n", ray->map_x, ray->map_y);
			break;
		}

		//printf("DDA step: map_x=%d, map_y=%d\n", ray->map_x, ray->map_y);

		// Check for wall hit
		if (game->data->map[ray->map_y][ray->map_x] > '0') {
			printf("Wall hit at: map_x=%d, map_y=%d\n", ray->map_x, ray->map_y);
			hit = 1;
		}
	}
}

void calculate_line_height(t_ray *ray) {
	// Fix wall distance calculations
	if (ray->side == 0 && ray->dir_x != 0) {
		ray->wall_dist = fabs((ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x);
	} else if (ray->side == 1 && ray->dir_y != 0) {
		ray->wall_dist = fabs((ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y);
	} else {
		ray->wall_dist = INFINITY; // Failsafe fallback
		fprintf(stderr, "Invalid wall distance: dir_x=%f, dir_y=%f\n", ray->dir_x, ray->dir_y);
	}

	// Avoid division by zero or large wall_dist issues
	if (ray->wall_dist <= 0 || isinf(ray->wall_dist)) {
		fprintf(stderr, "Wall distance invalid: wall_dist=%f\n", ray->wall_dist);
		ray->wall_dist = 1; // Fallback to prevent absurd values
	}

	// Compute wall slice dimensions
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);

	ray->draw_start = -(ray->line_height) / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0) ray->draw_start = 0;

	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT) ray->draw_end = WIN_HEIGHT - 1;

	// Debugging output
	printf("Wall Dist: %f, Line Height: %d, Draw Start: %d, Draw End: %d\n",
	       ray->wall_dist, ray->line_height, ray->draw_start, ray->draw_end);
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;

	// Ensure player_img is valid
	if (!game->player_img) {
		fprintf(stderr, "Error: player_img is uninitialized\n");
		return;
	}

	while (1)
	{
		// Bounds check for (x0, y0)
		if (x0 >= 0 && y0 >= 0 && x0 < WIN_WIDTH && y0 < WIN_HEIGHT) {
			mlx_put_pixel(game->player_img, x0, y0, color);
		} else {
			fprintf(stderr, "Pixel out of bounds: x=%d, y=%d\n", x0, y0);
		}

		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
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

void render_wall_slice(t_game *game, int x) {
	// Get the draw range for the wall slice
	int draw_start = game->ray->draw_start;
	int draw_end = game->ray->draw_end;

	// Draw the wall slice using the specified range
	for (int y = draw_start; y <= draw_end; y++) {
		mlx_put_pixel(game->player_img, x, y, 0xFFFFFF); // White for walls
	}
}

void raycasting(t_game *game) {
	for (int x = 0; x < WIN_WIDTH; x++) {
		// Initialize the ray for the current screen column
		set_ray(x, game);

		//printf("Ray %d: dir_x=%f, dir_y=%f, pos_x=%f, pos_y=%f\n",
		//       x, game->ray->dir_x, game->ray->dir_y, game->ray->pos_x, game->ray->pos_y);

		// Calculate stepping and initial distances
		set_dda(game->ray);

		// Perform DDA to find the intersection with a wall
		perform_dda(game, game->ray);

		//printf("Ray %d: map_x=%d, map_y=%d, side=%d\n",
		//       x, game->ray->map_x, game->ray->map_y, game->ray->side);

		// Calculate the wall height
		calculate_line_height(game->ray);

		//printf("Ray %d: wall_dist=%f, line_height=%d, draw_start=%d, draw_end=%d\n",
		//       x, game->ray->wall_dist, game->ray->line_height, game->ray->draw_start, game->ray->draw_end);

		// Draw the wall slice
		//render_wall_slice(game, x);
	}
}
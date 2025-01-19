#ifndef CUBE3D_EXEC_H
#define CUBE3D_EXEC_H


// include
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "parsing.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_ray {
	// Ray position and direction
	double pos_x;  // X-coordinate of ray's position
	double pos_y;  // Y-coordinate of ray's position
	double dir_x;  // X-direction of the ray
	double dir_y;  // Y-direction of the ray

	// Camera plane
	double plane_x;  // X-component of the camera plane
	double plane_y;  // Y-component of the camera plane

	// Map grid position
	int map_x;  // Current X grid position in the map
	int map_y;  // Current Y grid position in the map

	// Step and delta distances
	double deltadist_x;  // Distance to move in X to hit the next grid line
	double deltadist_y;  // Distance to move in Y to hit the next grid line
	double sidedist_x;   // Initial side distance in X
	double sidedist_y;   // Initial side distance in Y
	int step_x;          // Step direction in X (+1 or -1)
	int step_y;          // Step direction in Y (+1 or -1)

	// Collision info
	int side;         // 0 if X-axis wall hit, 1 if Y-axis wall hit
	double wall_dist; // Perpendicular distance to the wall
	double wall_x;    // Exact point the wall was hit (for texture calculation)

	// Rendering info
	int line_height;  // Height of the projected wall slice
	int draw_start;   // Start pixel of wall slice
	int draw_end;     // End pixel of wall slice

	// Camera offset
	double camera_x;  // Offset for the ray on the camera plane
} t_ray;

typedef struct s_player
{
	int         x;
	int         y;
	int         dir_x;
	int         dir_y;
	int         start_angle;
	int         end_angle;
}               t_player;

typedef struct s_game
{
	mlx_t       *mlx;
	mlx_image_t *n;
	mlx_image_t *s;
	mlx_image_t *e;
	mlx_image_t *w;
	mlx_image_t *player_img; // debug
	t_player    *player;
	int         *color_ceiling;
	int         *color_floor;
	int         map_h;
	int         map_w;
	t_data      *data;
	t_ray       *ray;
}               t_game;

int exec(t_data *data);
void init(t_game *game);

// moves
void left_right(t_game *game);
void wasd(t_game *game, mlx_key_data_t key);
void ft_hook(mlx_key_data_t keydata, void *param);
void raycasting(t_game *game);


int map_width(char **map);
int map_height(char **map);

#endif //CUBE3D_EXEC_H

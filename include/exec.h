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
# include <math.h>

# define FOV 60 // used to calculate the angle of the ray

typedef struct s_ray
{
	float fov_rd;
	double ray_angle;
	double wall_dist;
	int flag;
}	t_ray;

typedef struct s_player
{
	int         x; //position in pixel
	int         y;
	int         tile_x;
	int         tile_y;
	double      direction; // direction is on pi
}               t_player;

typedef struct s_game
{
	//mlx_image_t *player_img; // debug
	mlx_image_t *map_debug; // debug
	mlx_image_t *fpv;
	mlx_t       *mlx;
	int			map_w;
	int			map_h;
	t_player    *player;
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

// debug
void init_map(t_game *game);
void debug_player(t_game *game);

#endif //CUBE3D_EXEC_H

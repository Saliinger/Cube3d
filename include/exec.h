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
	mlx_image_t *ray;
	int inter_x;
	int inter_y;
	int step_x;
	int step_y;
	int wall_dist;
}	t_ray;

typedef struct s_player
{
	mlx_image_t *player_img; // debug
	int         x;
	int         y;
	int			angl;
}               t_player;

typedef struct s_game
{
	mlx_t       *mlx;
	mlx_image_t *n;
	mlx_image_t *s;
	mlx_image_t *e;
	mlx_image_t *w;
	// those img are useless we only need one img and put pixel to render the game
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

#endif //CUBE3D_EXEC_H

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

typedef struct s_ray
{
	double      pos_x;
	double      pos_y;
	double      dir_x;
	double      dir_y;
	double		plane_x;
	double		plane_y;
} t_ray;

typedef struct s_player
{
	int         x;
	int         y;
	int         direction;
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
	t_data      *data;
}               t_game;

int exec(t_data *data);
void init(t_game *game);

// moves
void left_right(t_game *game);
void wasd(t_game *game, mlx_key_data_t key);
void ft_hook(mlx_key_data_t keydata, void *param);
void raycasting(t_game *game);

#endif //CUBE3D_EXEC_H

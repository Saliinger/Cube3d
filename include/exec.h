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

enum e_direction {
	w,
	s,
	a,
	d
};

typedef struct s_ray
{
	int ray;
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
	t_player    *player;
	int         *color_ceiling;
	int         *color_floor;
	t_data      *data;
}               t_game;

int exec(t_data *data);
void init(t_game *game);

// moves
void left_right(t_game *game);
void wasd(t_game *game, enum e_direction direction);
void ft_hook(mlx_key_data_t keydata, void *param);
void raycasting(t_game *game);

#endif //CUBE3D_EXEC_H

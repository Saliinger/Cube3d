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
	double      sidedist_x;
	double      sidedist_y;
	double      deltadist_x;
	double      deltadist_y;
	int         map_x;
	int         map_y;
	double      camera_x;
	double      camera_y;
	double      step_x;
	double      step_y;
	double      side;
	double      wall_dist;
	double      line_height;
	double      draw_start;
	double      draw_end;
	double      wall_x;

} t_ray;

typedef struct s_player
{
	int         x;
	int         y;
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

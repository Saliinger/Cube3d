//
// Created by anoukan on 1/18/25.
//

#ifndef CUBE3D_EXEC_H
#define CUBE3D_EXEC_H


// include
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_player
{
	int x;
	int y;
} t_player;

typedef struct s_data
{
	mlx_t       *mlx;
	mlx_image_t *n;
	mlx_image_t *s;
	mlx_image_t *e;
	mlx_image_t *w;
	t_player *player_position;
}               t_data;

#endif //CUBE3D_EXEC_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:40:59 by jalbiser          #+#    #+#             */
/*   Updated: 2025/02/20 22:41:49 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// include
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "parsing.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>

# define FOV 60 // used to calculate the angle of the ray

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_texture;

typedef struct s_ray
{
	float			fov_rd;
	float			ray_angle;
	float			wall_dist;
	int				flag;
	int				index;
	float			vert_x;
	float			vert_y;
	float			horiz_x;
	float			horiz_y;
}					t_ray;

typedef struct s_player
{
	int				x;
	int				y;
	int				tile_x;
	int				tile_y;
	double			direction;
	int				move_ws;
	int				move_ad;
	int				move_lr;
}					t_player;

typedef struct s_game
{
	mlx_image_t		*fpv;
	mlx_t			*mlx;
	int				map_w;
	int				map_h;
	t_player		*player;
	t_data			*data;
	t_ray			*ray;
	t_texture		*texture;
}					t_game;

int					exec(t_data *data);
void				init(t_game *game);

// moves
void				left_right(t_game *game, int i);
void				wasd(t_game *game, mlx_key_data_t key);
void				ft_hook(mlx_key_data_t keydata, void *param);

int					map_width(char **map);
int					map_height(char **map);

// debug
void				init_map(t_game *game);
void				debug_player(t_game *game);

// raycasting
void				raycasting(t_game *game);
float				nor_angle(float angle);

// render
void				render_wall(t_game *game, int ray);
void				my_mlx_pixel_put(t_game *game, int x, int y, int color);
int					get_color(t_game *game, int flag);
mlx_texture_t		*get_texture(t_game *game, int flag);
int					reverse_bytes(int c);

#endif
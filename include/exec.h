/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:40:59 by jalbiser          #+#    #+#             */
/*   Updated: 2025/04/15 18:36:13 by anoukan          ###   ########.fr       */
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

# define FOV 60
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define ROTATION_SPEED 0.020
# define PLAYER_SPEED 5

# define TILE_SIZE 32

# define X_AXIS 1
# define Y_AXIS 0

typedef struct s_texture
{
	mlx_texture_t	*nord;
	mlx_texture_t	*sud;
	mlx_texture_t	*est;
	mlx_texture_t	*ouest;
}					t_texture;

typedef struct s_rayon
{
	float			wall_distance;
	float			angle;
	float			x_x;
	float			x_y;
	float			y_y;
	float			y_x;
	int				axis;
	float			top_pixel;
	float			bottom_pixel;
	float			wall_height;
}					t_rayon;

typedef struct s_window
{
	mlx_image_t		*fpv;
	mlx_t			*mlx;
	int				map_width;
	int				map_height;
	char			**map;

}					t_window;

typedef struct s_player
{
	float			angle;
	float			x;
	float			y;
	int				player_speed;
}					t_player;

typedef struct s_game
{
	t_texture		*texture;
	t_rayon			*rayon;
	t_window		*window;
	t_player		*player;
	t_data			*data;
	int				cursor;
	float			fov_rad;
}					t_game;

int					exec(t_data *data);

// 1) initialisation
void				init(t_game *game);
int					init_texture(t_game *game);
int					init_window(t_game *game);
int					init_player(t_game *game);
int					init_ray(t_game *game);

// 2) Raycasting
void				raycasting(t_game *game);
float				normalize_angle(float angle);
int					wall_hit(float x, float y, t_game *game);
int					unit_circle(float angle, char c);
int					inter_check(float angle, float *inter, float *step,
						int is_horizon);

// 3 exec
void				game_loop(void *param);
void				start_game(t_game *game);
void				render(t_game *game, int ray);
mlx_texture_t		*get_texture(t_game *game);
void				draw_floor_ceiling(t_game *game, float ray, float t_pix,
						float b_pix);
void				draw_wall(t_game *game, int ray);
void				game_loop(void *param);
void				move(void *param);
int					is_wall(float x, float y, t_game *game);

// utils
int					map_height(char **map);
int					map_width(char **map);
uint32_t			rgb_to_hex(uint32_t red, uint32_t green, uint32_t blue);
void				ft_free(t_game *game);
void				ft_exit(t_game *game, int status, char *str);

#endif
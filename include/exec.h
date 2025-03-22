/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:40:59 by jalbiser          #+#    #+#             */
/*   Updated: 2025/02/21 14:47:44 by jalbiser         ###   ########.fr       */
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
# define WIN_WIDTH 1900
# define WIN_HEIGHT 1000

# define ROTATION_SPEED 0.020 // rotation speed
# define PLAYER_SPEED 5       // player speed

# define TILE_SIZE 32

typedef struct	s_texture
{
	mlx_texture_t *nord;
	mlx_texture_t *sud;
	mlx_texture_t *est;
	mlx_texture_t *ouest;
}				t_texture;

typedef struct	s_rayon
{
	float	wall_distance;
	float	angle;
	float	x_x;
	float	x_y;
	float	y_y;
	float	y_x;
}				t_rayon;

typedef struct	s_window
{
	mlx_image_t *fpv;
	mlx_image_t *map_2d;
	mlx_t		*mlx;
	int			map_width;
	int			map_height;
	char		**map;

}				t_window;

typedef struct	s_player {
	float		angle;
	float		x;
	float		y;
}				t_player;

typedef struct	s_game
{
	t_texture	*texture;
	t_rayon		*rayon;
	t_window	*window;
	t_player	*player;
	t_data		*data;
	float		fov_rad;
}				t_game;

int					exec(t_data *data);

// 1) initialisation
void					init(t_game *game);
int						init_texture(t_game *game);
int						init_window(t_game *game);
int						init_player(t_game *game);
int						init_ray(t_game *game);

// 2) Raycasting
void raycasting(t_game *game);
float normalize_angle(float angle);
float inter_x(t_game *game, t_rayon *ray);
float inter_x(t_game *game, t_rayon *ray);
int wall_hit(char **map, float x, float y);


// 2d debug
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);

// utils
int	map_height(char **map);
int	map_width(char **map);


#endif
#include "../../include/cube3d.h"

void loop_hook(void *param)
{
	t_game *game = (t_game *)param;

	double move_speed = 0.05;
	double strafe_speed = 0.05;
	double rot_speed = 0.05;

	// Movement forward/backward
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player->x += game->player->dir_x * move_speed;
		game->player->y += game->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->x -= game->player->dir_x * move_speed;
		game->player->y -= game->player->dir_y * move_speed;
	}

	// Strafing left/right
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->x -= game->ray->plane_x * strafe_speed;
		game->player->y -= game->ray->plane_y * strafe_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->x += game->ray->plane_x * strafe_speed;
		game->player->y += game->ray->plane_y * strafe_speed;
	}

	// Rotation left/right
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		double old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-rot_speed) - game->player->dir_y * sin(-rot_speed);
		game->player->dir_y = old_dir_x * sin(-rot_speed) + game->player->dir_y * cos(-rot_speed);

		double old_plane_x = game->ray->plane_x;
		game->ray->plane_x = game->ray->plane_x * cos(-rot_speed) - game->ray->plane_y * sin(-rot_speed);
		game->ray->plane_y = old_plane_x * sin(-rot_speed) + game->ray->plane_y * cos(-rot_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		double old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(rot_speed) - game->player->dir_y * sin(rot_speed);
		game->player->dir_y = old_dir_x * sin(rot_speed) + game->player->dir_y * cos(rot_speed);

		double old_plane_x = game->ray->plane_x;
		game->ray->plane_x = game->ray->plane_x * cos(rot_speed) - game->ray->plane_y * sin(rot_speed);
		game->ray->plane_y = old_plane_x * sin(rot_speed) + game->ray->plane_y * cos(rot_speed);
	}

	raycasting(game);
}

void player_init(t_game *game)
{
	t_player *player;
	t_ray    *ray;

	// Allocate memory for player
	player = malloc(sizeof(t_player));
	if (!player) // Handle allocation failure
	{
		perror("Failed to allocate memory for player");
		exit(EXIT_FAILURE);
	}

	// Allocate memory for ray (this is missing in the problematic code)
	ray = malloc(sizeof(t_ray));
	if (!ray) // Handle allocation failure
	{
		perror("Failed to allocate memory for ray");
		free(player); // Free player to avoid memory leak
		exit(EXIT_FAILURE);
	}

	// Initialize player position
	player->x = game->data->player_x;
	player->y = game->data->player_y;

	// Initialize direction based on input
	if (game->data->player_direction == 'N')
	{
		player->dir_x = 0;  // Facing North
		player->dir_y = -1;
		ray->plane_x = 0.66;  // Slight FOV adjustment
		ray->plane_y = 0;
	}
	else if (game->data->player_direction == 'S')
	{
		player->dir_x = 0;  // Facing South
		player->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
	else if (game->data->player_direction == 'E')
	{
		player->dir_x = 1;  // Facing East
		player->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (game->data->player_direction == 'W')
	{
		player->dir_x = -1; // Facing West
		player->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}

	// Assign allocated and initialized structures to game
	game->player = player;
	game->ray = ray;
}

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	game.map_w = 5;
	game.map_h = 5;
	player_init(&game);
	init(&game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_key_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}

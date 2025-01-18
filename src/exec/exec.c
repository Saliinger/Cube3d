#include "../../include/exec.h"

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	init(&game);
	// add wasd listener
	// add left_right listener
    mlx_key_hook(game.mlx,  ft_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}

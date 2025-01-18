#include "../../include/exec.h"

int exec(t_data *data)
{
	t_game game;

	game.data = data;
    //printf("data:\n	no:%s\n	so:%s\n	we:%s\n	ea:%s\n", game.data->no_texture, game.data->no_texture, game.data->no_texture , game.data->no_texture);
	t_player player;

    player.x = data->player_x;
    player.y = data->player_y;

    game.player = &player;
	init(&game);
	// add wasd listener
	// add left_right listener
    mlx_key_hook(game.mlx,  ft_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}

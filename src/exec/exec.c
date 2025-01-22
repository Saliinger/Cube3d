#include "../../include/cube3d.h"

// void loop_hook(void *param)
// {
// 	t_game *game = (t_game *)param;
//
// }

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	init(&game);
	//mlx_loop_hook(game.mlx, loop_hook, &game);
	//mlx_key_hook(game.mlx, ft_hook, &game);
	raycasting(&game);
	mlx_loop(game.mlx);
	return (0);
}

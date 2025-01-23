#include "../../include/cube3d.h"

// loop will be use as a refresh on each move and will render everything
void loop_hook(void *param)
{
	t_game *game = (t_game *)param;
	mlx_delete_image(game->mlx , game->fpv);
	game->fpv = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	// add the hook for the player
	raycasting(game);
	mlx_image_to_window(game->mlx, game->fpv, 0, 0);
}

int exec(t_data *data)
{
	t_game game;

	game.data = data;
	init(&game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}

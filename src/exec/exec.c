#include "../../include/exec.h"

int					exec(t_data *data) {
	t_game	game;

	game.data = data;
	init(&game);

	return (0);
}
